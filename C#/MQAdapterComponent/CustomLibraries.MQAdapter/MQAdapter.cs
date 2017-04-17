using System;
using System.Text;
using System.Timers;
using System.Diagnostics;

using CustomLibraries.Utilities;
using IBM.WMQ;

namespace CustomLibraries.MQAdapter
{
	/// <summary>
	/// Summary description for MQAdapter.
	/// </summary>
	public class MQAdapter
	{
		private MQQueueManager mqQueueManager;
		private MQQueue mqPutQueue;
		private MQQueue mqGetQueue;
		
        private string mqQueueManagerName;
		private string mqRequestQueueName;
		private string mqResponseQueueName;

		private int characterSet;
        private int pollingTimeout;
        private const int WSMQ_DEFAULT_PORT = 1414;

		/// <summary>
		/// Instantiates the Queue Manager
		/// </summary>
		/// <param name="mqManager">The Queue Manager controlling the Request and Response Queues</param>
		public MQAdapter(string mqManager,string channel, string ipAddress,
			string putQueue,string getQueue,int timeout, int charSet, int port)
		{
			try
			{
				
				MQEnvironment.Hostname = ipAddress;
				MQEnvironment.Channel = channel;
				MQEnvironment.Port = 1000;

				mqQueueManagerName = mqManager;
				mqRequestQueueName = putQueue;
				mqResponseQueueName = getQueue;
				characterSet = charSet;

				pollingTimeout = timeout;
				// Connect to an MQ Manager, and share the connection handle with other threads
				mqQueueManager = new MQQueueManager(mqManager,channel, ipAddress);

				// Open Queue for Inquiry, Put Message in, and fail if Queue Manager is stopping
				mqPutQueue = mqQueueManager.AccessQueue(putQueue, MQC.MQOO_INQUIRE | 
					MQC.MQOO_OUTPUT | MQC.MQOO_FAIL_IF_QUIESCING | MQC.MQOO_SET_IDENTITY_CONTEXT);

				mqGetQueue = mqQueueManager.AccessQueue(getQueue,
					MQC.MQOO_INPUT_AS_Q_DEF + MQC.MQOO_FAIL_IF_QUIESCING);

			}	
			catch (MQException mqe)
			{
				throw new MQAdapterException("Error Code: " + 
					MQAdapterErrorReasons.GetMQFailureReasonErrorCode(mqe.Reason));
			}
		}
		
		
		/// <summary>
		/// Puts a message in an MQ Queue using the user Id provided
		/// <param name="message">The message to be put in the queue</param>
		/// <returns>Response message</returns>
		/// </summary>
		public string PushMQRequestMessage(string message)
		{
			try
			{
				MQMessage requestMessage = new MQMessage();

				requestMessage.Persistence = 0;

				requestMessage.ReplyToQueueName = mqResponseQueueName;
				requestMessage.ReplyToQueueManagerName = mqQueueManagerName;

				requestMessage.Format = MQC.MQFMT_STRING;
				requestMessage.CharacterSet = characterSet;
				requestMessage.MessageType = MQC.MQMT_REQUEST;
                requestMessage.MessageId = HexaDecimalUtility.ConvertToBinary(GenerateMQMsgId());
				requestMessage.CorrelationId = requestMessage.MessageId;

				MQPutMessageOptions pmo = new MQPutMessageOptions();
				pmo.Options = MQC.MQPMO_SET_IDENTITY_CONTEXT;

				requestMessage.WriteString(message);

				mqPutQueue.Put(requestMessage, pmo);

                string _msgId = BinaryUtility.ConvertToHexaDecimal(requestMessage.MessageId);

				return _msgId;

			}
			catch (MQException mqe)
			{
				// Close request Queue if still opened
				if(mqPutQueue.OpenStatus)
					mqPutQueue.Close();
				// Close Queue manager if still opened
				if(mqQueueManager.OpenStatus)
					mqQueueManager.Close();

				throw new MQAdapterException("Error Code: " + 
					MQAdapterErrorReasons.GetMQFailureReasonErrorCode(mqe.Reason));
			}
		}
		/// <summary>
		/// Get a message from an MQ Queue using a correlation id
		/// </summary>
		/// <param name="correlationId">correlation id</param>
		/// <returns>Response message</returns>
		public string GetMQResponseMessage(string correlationId)
		{
			MQMessage rsMsg = new MQMessage();
            rsMsg.CorrelationId = HexaDecimalUtility.ConvertToBinary(correlationId);
			
			MQGetMessageOptions gmo = new MQGetMessageOptions();
			gmo.Options = MQC.MQGMO_WAIT;
			gmo.MatchOptions = MQC.MQMO_MATCH_CORREL_ID;
			gmo.WaitInterval = pollingTimeout;

			try
			{
				mqGetQueue.Get(rsMsg,gmo);
				return rsMsg.ReadString(rsMsg.DataLength);
			}
			catch(MQException mqe)
			{
				// Close Reponse Queue if still opened
				if(mqGetQueue.OpenStatus)
					mqGetQueue.Close();
				// Close Queue manager if still opened
				if(mqQueueManager.OpenStatus)
					mqQueueManager.Close();
				
				// Check if it a timeout exception
				if(MQAdapterErrorReasons.GetMQFailureReasonErrorCode(mqe.Reason) == "MQRC_NO_MSG_AVAILABLE")
					throw new MQAdapterTimeoutException("Message with correlation Id " + correlationId + " Timed out");

				// MQ Exception
				throw new MQAdapterException("Error Code: " + 
					MQAdapterErrorReasons.GetMQFailureReasonErrorCode(mqe.Reason));
			}
		}
		/// <summary>
		/// Put a message for an MQ Queue and waits for an interval to get the resonse
		/// Throws an exception from type MQAdapterTimeoutException if the intervals expires
		/// </summary>
		/// <param name="message">The message to be put in the queue</param>
		/// <param name="user">The user to be impersonated</param>
		/// <returns>Response message</returns>
		public string SendMQRequestSync(string message)
		{
			string correlationId = PushMQRequestMessage(message);
			return GetMQResponseMessage(correlationId);
		}

		private string GenerateMQMsgId()
		{
			string _mqMsgID = System.Convert.ToString(System.Guid.NewGuid());
			_mqMsgID = _mqMsgID.Replace("-","");
			_mqMsgID = _mqMsgID.PadRight(48, '0');

			return _mqMsgID;
		}
	}
}
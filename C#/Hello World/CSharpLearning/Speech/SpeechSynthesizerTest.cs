using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Speech.AudioFormat;
using System.Speech.Synthesis;
using System.Text;
using System.Threading;
using NUnit.Framework;

namespace CSharpLearning.Speech
{
    [TestFixture]
    class SpeechSynthesizerTest
    {
        [Test]
        [TestCase("CBTC列车位置丢失")]
        [TestCase("编码处理器故障")]
        [TestCase("自动加载运行图失败")]
        public void SpeakTest1(string text)
        {
            var speak = new SpeechSynthesizer();

            speak.Rate = -1; // 设置语速,[-10,10]
            speak.Volume = 100; // 设置音量,[0,100]
            //speak.SelectVoice("Microsoft David Desktop");  
            //speak.SelectVoice("Microsoft Kangkang Desktop");
            speak.SelectVoiceByHints(VoiceGender.Male);
            //speak.SelectVoiceByHints(VoiceGender.Male, VoiceAge.Child, 2, CultureInfo.CurrentCulture);
            speak.Speak(text);

            //speak.SetOutputToWaveFile(string.Format("c:\\{0}.wav", text)); // 输出到文件
            //speak.Speak(text);

            //下面的代码为一些SpeechSynthesizer的属性，看实际情况是否需要使用
            speak.Dispose();  //释放所有语音资源
            //voice.SpeakAsyncCancelAll();  //取消朗读
            //voice.Speak("Hellow Word");  //同步朗读
            //voice.Pause();  //暂停朗读
            //voice.Resume(); //继续朗读
        }

        [Test]
        public void SpeakAsyncTest1()
        {
            var text = new List<string>()
            { 
                "这是第一段文字：最近，习近平总书记在纪念五四运动100周年大会上的重要讲话，在广大青年中引起强烈共鸣。总书记了解青年、理解青年，他的话朴实亲切，又催人奋进。一名青年的感想，道出了亿万年轻人的共同心声。", 
                "这是第二段文字：人生全靠演技。" 
            };

            int textCount = text.Count();
            var syncLock = new object();

            using(var speak = new SpeechSynthesizer())
            {
                speak.Rate = -1; // 设置语速,[-10,10]
                speak.Volume = 100; // 设置音量,[0,100]

                speak.SpeakCompleted += (object sender, SpeakCompletedEventArgs e) =>
                {
                    lock (syncLock) { if (--textCount == 0) Monitor.PulseAll(syncLock); }
                };

                text.ToList().ForEach(p => speak.SpeakAsync(p));

                lock(syncLock) Monitor.Wait(syncLock);
            }
        }

        [Test]
        public void GetInstalledVoicesTest1()
        {
            using (var synth = new SpeechSynthesizer())
            {
                // Output information about all of the installed voices.   
                Console.WriteLine("Installed voices -");
                foreach (InstalledVoice voice in synth.GetInstalledVoices())
                {
                    VoiceInfo info = voice.VoiceInfo;
                    string AudioFormats = "";
                    foreach (SpeechAudioFormatInfo fmt in info.SupportedAudioFormats)
                    {
                        AudioFormats += String.Format("{0}\n",
                        fmt.EncodingFormat.ToString());
                    }

                    Console.WriteLine(" Name:          " + info.Name);
                    Console.WriteLine(" Culture:       " + info.Culture);
                    Console.WriteLine(" Age:           " + info.Age);
                    Console.WriteLine(" Gender:        " + info.Gender);
                    Console.WriteLine(" Description:   " + info.Description);
                    Console.WriteLine(" ID:            " + info.Id);
                    Console.WriteLine(" Enabled:       " + voice.Enabled);
                    if (info.SupportedAudioFormats.Count != 0)
                    {
                        Console.WriteLine(" Audio formats: " + AudioFormats);
                    }
                    else
                    {
                        Console.WriteLine(" No supported audio formats found");
                    }

                    string AdditionalInfo = "";
                    foreach (string key in info.AdditionalInfo.Keys)
                    {
                        AdditionalInfo += String.Format("  {0}: {1}\n", key, info.AdditionalInfo[key]);
                    }

                    Console.WriteLine(" Additional Info - " + AdditionalInfo);
                    Console.WriteLine();
                }
            }
        }  
    }
}

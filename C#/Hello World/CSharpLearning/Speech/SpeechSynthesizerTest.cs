﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Speech.AudioFormat;
using System.Speech.Synthesis;
using System.Threading;
using System.Threading.Tasks;
using NUnit.Framework;

namespace CSharpLearning.Speech
{
    [TestFixture]
    class SpeechSynthesizerTest
    {
        [Test]
        [TestCase("列车 1 1 5 1 5 即将出库")]
        [TestCase("CBTC列车位置丢失")]
        public void Speak_Test1(string text)
        {
            using (var speak = new SpeechSynthesizer())
            {
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

                //voice.SpeakAsyncCancelAll();  //取消朗读
                //voice.Speak("Hellow Word");  //同步朗读
                //voice.Pause();  //暂停朗读
                //voice.Resume(); //继续朗读
            }
        }

        [Test(Description="一个SpeechSythesizer对象，连续调用SpeakAsyn方法。结果：两段文字依次播放")]
        public void SpeakAsyncTest1()
        {
            var text = new List<string>()
            { 
                @"这是第一段文字：最近，习近平总书记在纪念五四运动100周年大会上的重要讲话，在广大青年中引起强烈共鸣。
                总书记了解青年、理解青年，他的话朴实亲切，又催人奋进。一名青年的感想，道出了亿万年轻人的共同心声。", 
                                                                  
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

        [Test(Description = "两个SpeechSythesizer对象，连续调用SpeakAsyn方法。结果：两段文字同一时间重合播放。")]
        public void SpeakAsyncTest2()
        {
            var task1 = Task.Factory.StartNew(() =>
            {
                var text = new List<string>()
                { 
                    @"自动加载运行图失败", 
                                                                  
                    "这是第二段文字：人生全靠演技。" 
                };
                int textCount = text.Count();
                var syncLock = new object();

                using (var speak = new SpeechSynthesizer())
                {
                    speak.Rate = -1; // 设置语速,[-10,10]
                    speak.Volume = 100; // 设置音量,[0,100]

                    speak.SpeakCompleted += (object sender, SpeakCompletedEventArgs e) =>
                    {
                        lock (syncLock) { if (--textCount == 0) Monitor.PulseAll(syncLock); }
                    };

                    text.ToList().ForEach(p => speak.SpeakAsync(p));

                    lock (syncLock) Monitor.Wait(syncLock);
                }
            });

            
            var task2= Task.Factory.StartNew(() =>
            {
                var text = new List<string>()
                { 
                    @"两个Speech Sythesizer对象，连续调用SpeakAsyn方法。", 
                                                                  
                    "设置语速，设置音量" 
                };
                int textCount = text.Count();
                var syncLock = new object();

                using (var speak = new SpeechSynthesizer())
                {
                    speak.Rate = -1; // 设置语速,[-10,10]
                    speak.Volume = 100; // 设置音量,[0,100]

                    speak.SpeakCompleted += (object sender, SpeakCompletedEventArgs e) =>
                    {
                        lock (syncLock) { if (--textCount == 0) Monitor.PulseAll(syncLock); }
                    };

                    text.ToList().ForEach(p => speak.SpeakAsync(p));

                    lock (syncLock) Monitor.Wait(syncLock);
                }
            });

            task1.Wait();
            task2.Wait();
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

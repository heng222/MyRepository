using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Media;

namespace CSharpLearning.Media
{
    [TestFixture]
    class SoundPlayerTest
    {
        [Test, Description("播放系统事件声音")]
        public void Test1()
        {
            SystemSounds.Asterisk.Play();
            SystemSounds.Beep.Play();
            SystemSounds.Exclamation.Play();
            SystemSounds.Hand.Play();
            SystemSounds.Question.Play();
        }

        [Test, Description("同步播放自定义的WAV文件。")]
        public void Test2()
        {
            var player = new SoundPlayer();

            player.SoundLocation = @"D:\ATS\Plugins\Alarm\Config\wav\CBTC列车位置丢失.wav";      //音频文件路径 

            // 同步播放
            player.PlaySync();
        }

        [Test, Description("异步播放自定义的WAV文件。")]
        public void Test3()
        {
            var player = new SoundPlayer();

            player.SoundLocation = @"D:\ATS\Plugins\Alarm\Config\wav\CBTC列车位置丢失.wav";      //音频文件路径 

            // 异步播放
            player.Play();

            player.Stop();
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Configuration;
using ProWrite.Core;

namespace ProWrite.UI.Controls
{
    public class SpellCheckerList : StringList
    {
        public static void Load()
        {
            LoadStringListFromFile<SpellCheckerList>("CustomEnglish.dic");
        }
    }
}

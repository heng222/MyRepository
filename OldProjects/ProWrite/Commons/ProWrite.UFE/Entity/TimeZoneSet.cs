﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public class TimeZoneSet
    {
        public int Mode { get; set; }
        public string Location { get; set; }
    }

    //public enum TimeZoneType
    //{
        //AfricaAbidjan = "Africa/Abidjan",
        //AfricaAccra = "Africa/Accra",
        //AfricaAddis_Ababa = "Africa/Addis_Ababa",
        //AfricaAlgiers = "Africa/Algiers",
        //AfricaAsmara = "Africa/Asmara",
        //AfricaAsmera = "Africa/Asmera",
        //AfricaBamako = "Africa/Bamako",
        //AfricaBangui = "Africa/Bangui",
        //AfricaBanjul = "Africa/Banjul",
        //AfricaBissau = "Africa/Bissau",
        //AfricaBlantyre = "Africa/Blantyre",
        //AfricaBrazzaville = "Africa/Brazzaville",
        //AfricaBujumbura = "Africa/Bujumbura",
        //AfricaCairo = "Africa/Cairo",
        //AfricaCasablanca = "Africa/Casablanca",
        //AfricaCeuta = "Africa/Ceuta",
        //AfricaConakry = "Africa/Conakry",
        //AfricaDakar = "Africa/Dakar",
        //AfricaDar_es_Salaam = "Africa/Dar_es_Salaam",
        //AfricaDjibouti = "Africa/Djibouti",
        //AfricaDouala = "Africa/Douala",
        //AfricaEl_Aaiun = "Africa/El_Aaiun",
        //AfricaFreetown = "Africa/Freetown",
        //AfricaGaborone = "Africa/Gaborone",
        //AfricaHarare = "Africa/Harare",
        //AfricaJohannesburg = "Africa/Johannesburg",
        //AfricaKampala = "Africa/Kampala",
        //AfricaKhartoum = "Africa/Khartoum",
        //AfricaKigali = "Africa/Kigali",
        //AfricaKinshasa = "Africa/Kinshasa",
        //AfricaLagos = "Africa/Lagos",
        //AfricaLibreville = "Africa/Libreville",
        //AfricaLome = "Africa/Lome",
        //AfricaLuanda = "Africa/Luanda",
        //AfricaLubumbashi = "Africa/Lubumbashi",
        //AfricaLusaka = "Africa/Lusaka",
        //AfricaMalabo = "Africa/Malabo",
        //AfricaMaputo = "Africa/Maputo",
        //AfricaMaseru = "Africa/Maseru",
        //AfricaMbabane = "Africa/Mbabane",
        //AfricaMogadishu = "Africa/Mogadishu",
        //AfricaMonrovia = "Africa/Monrovia",
        //AfricaNairobi = "Africa/Nairobi",
        //AfricaNdjamena = "Africa/Ndjamena",
        //AfricaNiamey = "Africa/Niamey",
        //AfricaNouakchott = "Africa/Nouakchott",
        //AfricaOuagadougou = "Africa/Ouagadougou",
        //AfricaPortoNovo = "Africa/Porto-Novo",
        //AfricaSao_Tome = "Africa/Sao_Tome",
        //AfricaTimbuktu = "Africa/Timbuktu",
        //AfricaTripoli = "Africa/Tripoli",
        //AfricaTunis = "Africa/Tunis",
        //AfricaWindhoek = "Africa/Windhoek",
        //AsiaAden = "Asia/Aden",
        //AsiaAlmaty = "Asia/Almaty",
        //AsiaAmman = "Asia/Amman",
        //AsiaAnadyr = "Asia/Anadyr",
        //AsiaAqtau = "Asia/Aqtau",
        //AsiaAqtobe = "Asia/Aqtobe",
        //AsiaAshgabat = "Asia/Ashgabat",
        //AsiaAshkhabad = "Asia/Ashkhabad",
        //AsiaBaghdad = "Asia/Baghdad",
        //AsiaBahrain = "Asia/Bahrain",
        //AsiaBaku = "Asia/Baku",
        //AsiaBangkok = "Asia/Bangkok",
        //AsiaBeirut = "Asia/Beirut",
        //AsiaBishkek = "Asia/Bishkek",
        //AsiaBrunei = "Asia/Brunei",
        //AsiaCalcutta = "Asia/Calcutta",
        //AsiaChoibalsan = "Asia/Choibalsan",
        //AsiaChongqing = "Asia/Chongqing",
        //AsiaChungking = "Asia/Chungking",
        //AsiaColombo = "Asia/Colombo",
        //AsiaDacca = "Asia/Dacca",
        //AsiaDamascus = "Asia/Damascus",
        //AsiaDhaka = "Asia/Dhaka",
        //AsiaDili = "Asia/Dili",
        //AsiaDubai = "Asia/Dubai",
        //AsiaDushanbe = "Asia/Dushanbe",
        //AsiaGaza = "Asia/Gaza",
        //AsiaHarbin = "Asia/Harbin",
        //Asia/Ho_Chi_Minh="",
        //Asia/Hong_Kong="",
        //Asia/Hovd="",
        //Asia/Irkutsk="",
        //Asia/Istanbul="",
        //Asia/Jakarta="",
        //Asia/Jayapura="",
        //Asia/Jerusalem="",
        //Asia/Kabul="",
        //Asia/Kamchatka="",
        //Asia/Karachi="",
        //Asia/Kashgar="",
        //Asia/Katmandu="",
        //Asia/Kolkata="",
        //Asia/Krasnoyarsk="",
        //Asia/Kuala_Lumpur="",
        //Asia/Kuching="",
        //Asia/Kuwait="",
        //Asia/Macao="",
        //Asia/Macau="",
        //Asia/Magadan="",
        //Asia/Makassar="",
        //Asia/Manila="",
        //Asia/Muscat="",
        //Asia/Nicosia="",
        //Asia/Novosibirsk="",
        //Asia/Omsk="",
        //Asia/Oral="",
        //Asia/Phnom_Penh="",
        //Asia/Pontianak="",
        //Asia/Pyongyang="",
        //Asia/Qatar="",
        //Asia/Qyzylorda="",
        //Asia/Rangoon="",
        //Asia/Riyadh="",
        //Asia/Riyadh87="",
        //Asia/Riyadh88="",
        //Asia/Riyadh89="",
        //Asia/Saigon="",
        //Asia/Sakhalin="",
        //Asia/Samarkand="",
        //Asia/Seoul="",
        //Asia/Shanghai="",
        //Asia/Singapore="",
        //Asia/Taipei="",
        //Asia/Tashkent="",
        //Asia/Tbilisi="",
        //Asia/Tehran="",
        //Asia/Tel_Aviv="",
        //Asia/Thimbu="",
        //Asia/Thimphu="",
        //Asia/Tokyo="",
        //Asia/Ujung_Pandang="",
        //Asia/Ulaanbaatar="",
        //Asia/Ulan_Bator="",
        //Asia/Urumqi="",
        //Asia/Vientiane="",
        //Asia/Vladivostok="",
        //Asia/Yakutsk="",
        //Asia/Yekaterinburg="",
        //Asia/Yerevan="",
        //Canada/Atlantic="",
        //Canada/Central="",
        //Canada/East-Saskatchewan="",
        //Canada/Eastern="",
        //Canada/Mountain="",
        //Canada/Newfoundland="",
        //Canada/Pacific="",
        //Canada/Saskatchewan="",
        //Canada/Yukon="",
        //Europe/Amsterdam="",
        //Europe/Andorra="",
        //Europe/Athens="",
        //Europe/Belfast="",
        //Europe/Belgrade="",
        //Europe/Berlin="",
        //Europe/Bratislava="",
        //Europe/Brussels="",
        //Europe/Bucharest="",
        //Europe/Budapest="",
        //Europe/Chisinau="",
        //Europe/Copenhagen="",
        //Europe/Dublin="",
        //Europe/Gibraltar="",
        //Europe/Guernsey="",
        //Europe/Helsinki="",
        //Europe/Isle_of_Man="",
        //Europe/Istanbul="",
        //Europe/Jersey="",
        //Europe/Kaliningrad="",
        //Europe/Kiev="",
        //Europe/Lisbon="",
        //Europe/Ljubljana="",
        //Europe/London="",
        //Europe/Luxembourg="",
        //Europe/Madrid="",
        //Europe/Malta="",
        //Europe/Mariehamn="",
        //Europe/Minsk="",
        //Europe/Monaco="",
        //Europe/Moscow="",
        //Europe/Nicosia="",
        //Europe/Oslo="",
        //Europe/Paris="",
        //Europe/Podgorica="",
        //Europe/Prague="",
        //Europe/Riga="",
        //Europe/Rome="",
        //Europe/Samara="",
        //Europe/San_Marino="",
        //Europe/Sarajevo="",
        //Europe/Simferopol="",
        //Europe/Skopje="",
        //Europe/Sofia="",
        //Europe/Stockholm="",
        //Europe/Tallinn="",
        //Europe/Tirane="",
        //Europe/Tiraspol="",
        //Europe/Uzhgorod="",
        //Europe/Vaduz="",
        //Europe/Vatican="",
        //Europe/Vienna="",
        //Europe/Vilnius="",
        //Europe/Volgograd="",
        //Europe/Warsaw="",
        //Europe/Zagreb="",
        //Europe/Zaporozhye="",
        //Europe/Zurich="",
        //Mexico/BajaNorte="",
        //Mexico/BajaSur="",
        //Mexico/General="",
        //US/Alaska="",
        //US/Aleutian="",
        //US/Arizona="",
        //US/Central="",
        //US/East-Indiana="",
        //US/Eastern="",
        //US/Hawaii="",
        //US/Indiana-Starke="",
        //US/Michigan="",
        //US/Mountain="",
        //US/Pacific="",
    //}
}

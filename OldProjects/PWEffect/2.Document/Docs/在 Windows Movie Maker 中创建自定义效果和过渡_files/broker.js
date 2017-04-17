if (!window.SR_G) {
var SR_Cf = new Object();
var SR_G = new Object();
var SR_Ct = new Object();
SR_G.pF = false;
SR_G.empty = false;
SR_Ct.browser = new Object();
SR_Ct.browser.iE = 'Microsoft Internet Explorer';
SR_Ct.browser.mz = 'Netscape';
SR_Ct.browser.opera = 'Opera';
SR_G.bn = navigator.appName;
SR_G.bv = parseInt(navigator.appVersion);
SR_G.iIE = false;
SR_G.iMz = false;
SR_G.isInternetExplorer7 = false;
if (SR_G.bn == SR_Ct.browser.iE)
{
if (SR_G.bv > 3)
{
var a = navigator.userAgent.toLowerCase();
if (a.indexOf("msie 5.0") == -1 && a.indexOf("msie 5.0") == -1)
{
SR_G.iIE = true;
}
if (a.indexOf("msie 7") != -1)
{
SR_G.isInternetExplorer7 = true;
}
}
}
if (SR_G.bn == SR_Ct.browser.mz)
{
if (SR_G.bv > 4)
{
SR_G.iMz = true;
}
}
if (SR_G.bn == SR_Ct.browser.opera)
{
SR_G.iMz = true;// treat the same as Mozilla
}
SR_Ct.cLT = new Object();
SR_Ct.cLT.dr = 1;
SR_Ct.cLT.eD = 2;
SR_Ct.iT = new Object();
SR_Ct.iT.standard = 0;
SR_Ct.iT.email = 1;
SR_Ct.iT.dD = 2;
SR_Ct.iT.emailDomainDeparture = 3;
SR_Ct.cT = new Object();
SR_Ct.cT.aA = 1;
SR_Ct.cT.iP = 2;
SR_Ct.cT.emailDomainDeparture = 3;
SR_Ct.hA = new Object();
SR_Ct.hA.left = 0;
SR_Ct.hA.middle = 1;
SR_Ct.hA.right = 2;
SR_Ct.vA = new Object();
SR_Ct.vA.top = 0;
SR_Ct.vA.middle = 1;
SR_Ct.vA.bottom = 2;
SR_Cf.cN = 'msresearch';
SR_Cf.Do = '.microsoft.com';
SR_Cf.cP = '/';
SR_Ct.cJC = ':';
SR_Cf.cLT = 1;
SR_Cf.Du = 90 * 86400000;
SR_Cf.rapidCookieDuration = 0 * 86400000;
SR_Cf.listenerUrl = '';// //
function SR_KA()
{
this.kAPD = 1000;
this.id = Math.random();
this.aS = KA_aS;
this.cC = KA_cC;
this.iPCE = KA_iPCE;
this.cookieExists = KeepAlive_cookieExists;
function KA_aS()
{
if (this.iPCE())
{
setInterval('SR_G.kA.cC()', this.kAPD);
}
else
{
if (this.cookieExists(SR_Ct.cT.emailDomainDeparture))
{
var c = document.cookie.toString();
var index = c.indexOf(SR_Cf.cN + '=' + SR_Ct.cT.emailDomainDeparture);
var ec = c.length;
c = c.substring(index, ec);
var i1 = c.indexOf(';');
if (i1 != -1) c = c.substring(0, i1);
var i2 = c.indexOf('=');
c = c.substring(i2 + 1);
var vs = c.split(':');
if (vs.length == 2)
{
var url = SR_Cf.listenerUrl;
url += (url.indexOf('?') == -1 ? '?' : '&');
url += 'action=log'
+ '&user=' + vs[1]
+ '&location=' + escape(window.location);
setTimeout("var i = new Image(); i.src = '" + url + "&' + (new Date()).getTime(); ", 5);
}
}
}
}
function KA_cC()
{
if (this.iPCE())
{
var c = SR_Cf.cN + '=' + SR_Ct.cT.iP
+ ':' + escape(document.location)
+ ':' + (new Date()).getTime()
+ ':' + this.id
+ '; path=' + SR_Cf.cP;
if (SR_Cf.Do != '')
{
c += '; domain=' + SR_Cf.Do;
}
document.cookie = c;
}
}
function KA_iPCE()
{
return this.cookieExists(SR_Ct.cT.iP);
}
function KeepAlive_cookieExists(cT)
{
var c = SR_Cf.cN + '=' + cT;
if (document.cookie.indexOf(c) != -1)
{
return true;
}
return false;
}
}
SR_G.kA = new SR_KA();
SR_G.kA.aS();
function SR_PCB()
{
this.m = [
['(code\\.msdn\\.microsoft\\.com|cpapp02)', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_CODE-p26386365_661-p15808382mt.js', 0, null],
['/(social\\.expression\\.microsoft)[\\w\\.-]+/(f|F)orums/(en|EN)-(us|US)/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_EXPRESSION-p26386365-669.js', 1, null],
['/(social\\.expression\\.microsoft)[\\w\\.-]+/(en|EN)-(us|US)/(p|P)rofile/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_EXPRESSION-p26386365-670.js', 1, null],
['/(social\\.expression\\.microsoft)[\\w\\.-]+/(s|S)earch/(en|EN)-(us|US)/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_EXPRESSION-p26386365-668.js', 0, null],
['/(social\\.expression\\.microsoft)[\\w\\.-]+/(en|EN)-(us|US)/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_EXPRESSION-p26386365-671.js', 0, null],
['/(expression\\.microsoft)[\\w\\.-]+/(en|EN)-(us|US)/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_EXPRESSION-p26386365-667.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/de-', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382mt-689.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/en-(?!us)', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-685.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/en-au/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-p15466742-en-au.js', 1, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/en-us/library/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-p26386365_TIER1.js', 1, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/en-us/(vcsharp|vbasic|office|vs2008|windowsvista|asp\\.net|netframework|vstudio)/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-p26386365_TIER3.js', 1, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/en-us/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-p26386365_TIER4.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/en-us/magazine/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-p26386365_MAG.js', 1, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/fr-ca/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382mt-687.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/fr-fr/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382mt-fr-fr.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/hi-in/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-353.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/it-it/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p17637473-700.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/ru-', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382mt-683.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/zh-cn/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382mt-289.js', 0, null],
['/(sr-msdn|msdnstage|msdntest|msdnlive|msdn\\.microsoft)[\\w\\.-]+/en-us/(default\\.aspx|subscriptions|community|downloads|support|chats|events|aa|bb|cc|ms)', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382mt.js', 1, null],
['(.*?social\\.msdn\\.microsoft)[\\w\\.-/]+/en-us/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-p26386365_659.js', 0, null],
['(.*?social\\.msdn\\.microsoft)[\\w\\.-/]+/((profile/en-us)|(en-us/profile))', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-660.js', 1, null],
['(.*?social\\.msdn\\.microsoft)[\\w\\.-/]+/search/en-us', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-310.js', 1, null],
['(.*?social\\.msdn\\.microsoft)[\\w\\.-/]+/forums/en-us', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_MSDN-p15808382-p26386365_632.js', 2, null],
['(.*?social\\.technet\\.microsoft)[\\w\\.-/]+/en-us/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-p26386365_663.js', 1, null],
['(.*?social\\.technet\\.microsoft)[\\w\\.-/]+/((profile/en-us)|(en-us/profile))', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-664.js', 1, null],
['(.*?social\\.technet\\.microsoft)[\\w\\.-/]+/forums/en-us', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-p26386365_633.js', 2, null],
['(.*?social\\.technet\\.microsoft)[\\w\\.-/]+/search/en-us', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-313.js', 1, null],
['/(social\\.microsoft)[\\w\\.-]+/(f|F)orums/(en|EN)', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_SOCIAL-p26386365-698.js', 1, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/de-', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382mt-690.js', 0, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/en-(?!us)', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382mt-686.js', 0, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/en-au/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-p15466742-en-au.js', 1, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/en-us/library/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-p26386365_74-TIER1.js', 1, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/en-us/(security|sysinternals)/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-p26386365_74-TIER2.js', 1, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/en-us/(solutionaccelerators|office|updatemanagement|exchange|wsus|windows|windowsserver)/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-p26386365_74-TIER3.js', 1, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/en-us/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-p26386365_74-TIER4.js', 0, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/en-us/magazine/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-p26386365_74-MAG.js', 1, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/fr-', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382mt-688.js', 0, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/fr-fr/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382mt-fr-fr.js', 1, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/hi-in/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382-356.js', 0, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/it-it/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TechNet-p176374730-IT.js', 0, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/ru-', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382mt-684.js', 0, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/zh-cn/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382mt-290.js', 0, null],
['/(sr-technet|tnstage|tnlive|tntest|technet\\.microsoft)[\\w\\.-]+/en-us/(default\\.aspx|subscriptions|community|support|events|downloads|ms|bb|cc)', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_TN-p15808382mt.js', 1, null],
['//(sr-www|wwwstaging|www\\.microsoft)[\\w\\.-]+/express/', 'http://js.microsoft.com/library/svy/sto/SiteRecruit_PageConfiguration_WWW-p26386365-673.js', 0, null],
];
this.st = PCB_s;
this.gCP = PCB_gFP;
this.lC = PCB_lC;
function PCB_s(url)
{
var cfr = this.gCP(url);
if (cfr != null)
{
this.lC(cfr);
}
}
function PCB_gFP(url)
{
var cS = 0;
var cM = -1;
for (var i = 0; i < this.m.length; i++)
{
if (this.m[i] != null)
{
var r = new RegExp(this.m[i][0], 'i');
if (url.toString().search(r) != -1)
{
var prereqs = this.m[i][3];
var matchPrereqs = true;
if (prereqs != null)
{
for (var j = 0; j < prereqs.length; j++)
{
var p = prereqs[j];
if (p != null)
{
if (p.elementType)
{
var matchContent = false;
var matchAttribute = false;
var elements = document.getElementsByTagName(p.elementType);
for (var k = 0; k < elements.length; k++)
{
if (p.contentValue != '')
{
if (elements[k].innerHTML.search(p.contentValue) != -1)
{
matchContent = true;
}
}
else
{
matchContent = true;
}
if (p.attributeName != '')
{
var a = elements[k].attributes.getNamedItem(p.attributeName);
if (a != null)
{
if (p.attributeValue != '')
{
if (a.value.search(p.attributeValue) != -1)
{
matchAttribute = true;
}
}
else
{
matchAttribute = true;
}
}
}
else
{
matchAttribute = true;
}
}
if (!matchContent || !matchAttribute)
{
matchPrereqs = false;
break;
}
}
else if (p.cN)
{
var cookieTemplate = p.cN + '=';
if (p.cookieValue)
{
cookieTemplate += p.cookieValue;
}
if (document.cookie.indexOf(cookieTemplate) == -1)
{
matchPrereqs = false;
break;
}
}
else if (p.language)
{
if (navigator.language && navigator.language.toString().toLowerCase().indexOf(p.language) == -1)
{
matchPrereqs = false;
break;
}
else if (navigator.userLanguage && navigator.userLanguage.toString().toLowerCase().indexOf(p.language) == -1)
{
matchPrereqs = false;
break;
}
}
}
}
}
else
{
matchPrereqs = true;
}
if (matchPrereqs)
{
var nS = this.m[i][2];
if (nS >= cS)
{
cM = i;
cS = nS;
}
}
}
}
}
var page = null;
if (cM >= 0)
{
page = this.m[cM][1];
}
return page;
}
function PCB_lC(cfr)
{
document.write('<script language="JavaScript" src="' + cfr + '"></script>');
}
}
try
{
if (SR_G.iIE || SR_G.iMz)
{
SR_G.broker = new SR_PCB();
SR_G.broker.st(window.location);
}
}
catch (e)
{
}
SR_G.pF = true;
}

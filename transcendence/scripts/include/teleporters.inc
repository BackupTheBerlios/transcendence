use uo;
use os;
use cfgfile;

var teleporters := {
////yew to t2a tunnel
    { 312,   786,  -24,    5748,   361,    2},
    { 313,   786,  -24,    5749,   361,    2},
    { 314,   786,  -24,    5750,   361,    4},
    {5748,   362,    2,     312,   787,  -24},
    {5749,   362,    0,     313,   787,  -24},
    {5750,   362,    3,     314,   787,  -24},
           
////jhelom teleporters
    {1142,  3621,    5,    1414,  3828,    5},
    {1406,  3996,    5,    1414,  3828,    5},
    {1409,  3824,    5,    1124,  3623,    5},
    {1419,  3832,    5,    1466,  4015,    5},

//// moonglow teleporters
    {4300,   968,    5,    4442,  1122,    5},
    {4436,  1107,    5,    4300,   992,    5},
    {4443,  1137,    5,    4487,  1475,    5},
    {4449,  1107,    5,    4539,   890,   28},
    {4449,  1115,    5,    4671,  1135,   10},
    {4496,  1475,   15,    4442,  1122,    5},
    {4540,   898,   32,    4442,  1122,    5},
    {4663,  1134,   13,    4442,  1122,    5},

////hedge maze
    {1163,  2208,   60,    1171,  2202,    0},
    {1165,  2205,   40,    1163,  2209,   60},
    {1166,  2237,   60,    1163,  2208,    0},

////destard
//enterance
    {1175,  2635,    0,    5242,  1006,    0},
    {1176,  2635,    0,    5243,  1006,    0},
    {1177,  2635,    0,    5244,  1006,    0},
    {5242,  1007,    0,    1175,  2636,    0},
    {5243,  1007,    0,    1176,  2636,    0},
    {5244,  1007,    0,    1177,  2636,    0},
//lvl1 - lvl2
    {5129,   909,  -28,    5142,   798,   17},
    {5130,   909,  -28,    5143,   798,   17},
    {5131,   909,  -28,    5144,   798,   17},
    {5132,   909,  -28,    5145,   798,   17},
    {5142,   797,   22,    5129,   908,  -28},
    {5143,   797,   22,    5130,   908,  -28},
    {5144,   797,   22,    5131,   908,  -28},
    {5145,   797,   22,    5132,   908,  -28},
//lvl2 - lvl3 
    {5153,   808,  -25,    5134,   984,   17},
    {5153,   809,  -25,    5134,   985,   17},
    {5153,   810,  -25,    5134,   986,   17},
    {5153,   811,  -25,    5134,   987,   17},
    {5133,   984,   22,    5152,   808,  -19},
    {5133,   985,   22,    5152,   809,  -19},
    {5133,   986,   22,    5152,   810,  -19},
    {5133,   987,   22,    5152,   811,  -19},

////shame
//enterance
    { 512,  1559,    0,    5394,   126,    0},
    { 513,  1559,    0,    5395,   126,    0},
    { 514,  1559,    0,    5396,   126,    0},
    {5394,   127,    0,     512,  1560,    0},
    {5395,   127,    0,     513,  1560,    0},
    {5396,   127,    0,     514,  1560,    0},
//lvl1 - lvl2
    {5490,    19,  -30,    5514,    10,    0},
    {5514,    10,    0,    5490,    19,  -30},
//lvl2 - lvl3
    {5604,   102,    5,    5514,   148,   25},
    {5514,   148,   25,    5604,   102,    5},
//lvl3 - lvl4
    {5538,   170,    5,    5513,   176,    5},
    {5513,   176,    5,    5538,   170,    5},
//lvl4 - lvl5
    {5507,   162,    5,    5875,    19,   -5},
    {5875,    19,   -5,    5507,   162,    5},

////deceit
//enterance
    {4110,   430,    5,    5187,   638,    0},
    {4111,   430,    5,    5188,   638,    0},
    {4112,   430,    5,    5189,   638,    0},
    {5187,   639,    0,    4110,   431,    5},
    {5188,   639,    0,    4111,   431,    5},
    {5189,   639,    0,    4112,   431,    5},
//lvl1 - lvl2
    {5216,   587,  -18,    5304,   531,   12},
    {5217,   587,  -18,    5305,   531,   12},
    {5218,   587,  -18,    5306,   531,   12},
    {5304,   530,   17,    5216,   586,  -13},
    {5305,   530,   17,    5217,   586,  -13},
    {5306,   530,   17,    5218,   586,  -13},
//lvl2 - lvl3
    {5346,   578,    5,    5137,   649,    5},
    {5137,   649,    5,    5346,   578,    5},
//lvl3 - lvl4
    {5218,   761,  -28,    5305,   650,   12},
    {5219,   761,  -28,    5306,   650,   12},
    {5305,   649,   17,    5218,   760,    1},
    {5306,   549,   17,    5219,   760,    1},

////wrong
//enterance
    {2041,   215,   14,    5824,   630,    0},
    {2042,   215,   14,    5825,   630,    0},
    {2043,   215,   14,    5826,   630,    0},
    {5824,   631,    0,    2041,   216,   14},
    {5825,   631,    0,    2042,   216,   14},
    {5826,   631,    0,    2043,   216,   14},
//lvl1 - lvl2
    {5826,   592,    0,    5690,   569,   25},
    {5690,   569,   25,    5826,   592,    0},
//lvl2 - lvl3
    {5736,   551,   20,    5703,   639,    0},
    {5698,   662,    0,    5736,   551,   20},

////despise
//enterance
    {1296,  1080,    0,    5587,   630,   30},
    {1296,  1081,    0,    5587,   631,   30},
    {1296,  1082,    0,    5587,   632,   30},
    {5588,   630,   30,    1297,  1080,    0},
    {5588,   631,   30,    1297,  1081,    0},
    {5588,   632,   30,    1297,  1082,    0},
//lvl1 - lvl2
    {5570,   628,   57,    5504,   569,   46},
    {5570,   629,   57,    5504,   570,   46},
    {5570,   630,   57,    5504,   571,   46},
    {5505,   569,   41,    5571,   628,   52},
    {5505,   570,   41,    5571,   629,   52},
    {5505,   571,   41,    5571,   630,   52},
//lvl2 - lvl3
    {5571,   632,   12,    5522,   672,   32},
    {5571,   633,   12,    5522,   673,   32},
    {5571,   634,   12,    5522,   674,   32},
    {5523,   672,   37,    5572,   632,   17},
    {5523,   673,   37,    5572,   633,   17},
    {5523,   674,   37,    5572,   634,   17},
//lvl3 - lvl4
    {5385,   755,  -13,    5410,   858,   57},
    {5385,   756,  -13,    5410,   859,   57},
    {5385,   757,  -13,    5410,   860,   57},
    {5411,   858,   62,    5386,   755,   -8},
    {5411,   859,   62,    5386,   756,   -8},
    {5411,   860,   62,    5386,   757,   -8},

////covetous
//entrance
    {5455,  1864,    0,    2498,   917,    0},
    {5456,  1864,    0,    2499,   917,    0},
    {5457,  1864,    0,    2500,   917,    0},
    {2498,   916,    0,    5455,  1863,    0},
    {2499,   916,    0,    5456,  1863,    0},
    {2500,   916,    0,    5457,  1863,    0},
//lvl1 - lvl2
    {5392,  1959,    0,    2420,   883,    0},
    {5393,  1959,    0,    2421,   883,    0},
    {5394,  1959,    0,    2422,   883,    0},
    {2420,   884,    0,    5392,  1958,    0},
    {2421,   884,    0,    5393,  1958,    0},
    {2422,   884,    0,    5394,  1958,    0},
//lvl2 - lvl3
    {2384,   836,    0,    5614,  1996,    0},
    {2384,   837,    0,    5614,  1997,    0},
    {2384,   838,    0,    5614,  1998,    0},
    {5615,  1996,    0,    2385,   836,    0},
    {5615,  1997,    0,    2385,   837,    0},
    {5615,  1998,    0,    2385,   838,    0},
//lvl3 - lvl4
    {5388,  2027,    0,    2455,   859,    0},
    {5389,  2027,    0,    2456,   859,    0},
    {5390,  2027,    0,    2457,   859,    0},
    {2455,   858,    0,    5388,  2026,    0},
    {2456,   858,    0,    5389,  2026,    0},
    {2457,   858,    0,    5390,  2026,    0},
//lvl4 - lvl5
    {2544,   846,    0,    5578,  1926,    0},
    {2545,   846,    0,    5579,  1926,    0},
    {2546,   846,    0,    5580,  1926,    0},
    {5578,  1927,    0,    2544,   847,    0},
    {5579,  1927,    0,    2545,   847,    0},
    {5580,  1927,    0,    2546,   847,    0},
//lvl5-lvl6a
    {5556,  1827,  -15,    5551,  1805,   12},
    {5557,  1827,  -15,    5552,  1805,   12},
    {5551,  1804,   17,    5556,  1826,  -10},
    {5552,  1804,   17,    5556,  1826,  -10},
    {5552,  1804,   17,    5557,  1826,  -10},
//lvl5 - lvl6b
    {5595,  1840,  -14,    5466,  1804,   12},
    {5595,  1841,  -14,    5466,  1805,   12},
    {5465,  1804,   17,    5594,  1840,   -9},
    {5465,  1805,   17,    5594,  1841,   -9},
    {5465,  1805,   17,    5594,  1841,   -9},

////hythloth
//enterance
    {5904,    17,   61,    4721,  3814,    0},
    {5905,    17,   61,    4722,  3814,    0},
    {5906,    17,   61,    4723,  3814,    0},
    {4721,  3813,    0,    5904,    18,   56},
    {4722,  3813,    0,    5905,    18,   56},
    {4723,  3813,    0,    5906,    18,   56},
//lvl1 - lvl2
    {5905,    97,    0,    5976,   169,    0},
    {5976,   169,    0,    5905,    97,    0},
    {5976,   168,    0,    5905,    97,    0},
    {5977,   169,    0,    5905,    97,    0},
    {5977,   168,    0,    5905,    97,    0},
//lvl2 - lvl3
    {5922,   168,    7,    6081,   144,  -10},
    {5922,   169,    7,    6081,   145,  -10},
    {5922,   170,    7,    6081,   146,  -10},
    {6080,   144,   -5,    5921,   169,   11},
    {6080,   145,   -5,    5921,   169,   12},
    {6080,   146,   -5,    5921,   169,   11},
//lvl3 - lvl4
    {6041,   192,    7,    6057,    87,   34},
    {6041,   193,    7,    6057,    89,   34},
    {6041,   194,    9,    6057,    90,   34},
    {6056,    87,   39,    6040,   192,   12},
    {6056,    89,   39,    6040,   193,   12},
    {6056,    90,   39,    6040,   194,   12},

////wind
//enterance
    {5166,   245,   15,    1361,   883,    0},
    {1361,   883,    0,    5166,   245,   15},
//NE exit
    {5191,   152,    0,    1361,   883,    0},
// wind - park
    {5200,    71,   17,    5211,    22,   15},
    {5217,    18,   15,    5200,    71,   17},
    
////ice dungeon
//enterance
    {5882,   241,    0,    1997,    81,    7},
    {5882,   242,    0,    1997,    81,    7},
    {5882,   243,    0,    1997,    81,    7},
    {1997,    81,    7,    5881,   242,    0},
//lvl1 - orc fort
    {5849,   238,  -25,    5831,   324,   27},
    {5850,   238,  -25,    5832,   324,   26},
    {5851,   238,  -25,    5833,   324,   28},
    {5852,   238,  -25,    5834,   324,   27},
    {5853,   238,  -23,    5835,   324,   27},
    {5831,   323,   34,    5849,   237,  -24},
    {5832,   323,   34,    5850,   237,  -24},    
    {5833,   323,   33,    5851,   237,  -24},    
    {5834,   323,   33,    5852,   237,  -25},
    {5835,   323,   33,    5853,   237,  -23},
//lvl1 - lvl2
    {5704,   145,  -45,    5705,   305,   12},
    {5704,   146,  -45,    5705,   306,   12},   
    {5704,   147,  -45,    5705,   307,   12},  
    {5706,   303,   12,    5705,   146,  -45},
    {5706,   304,   12,    5705,   146,  -45},
    {5706,   305,   12,    5705,   146,  -45},
    {5706,   306,   12,    5705,   147,  -45},
    {5706,   307,   12,    5705,   147,  -45},
    {5706,   308,   12,    5705,   147,  -45},
//lvl1 - t2a exit
    {5872,   144,   32,    5203,  2327,   27}, 
    {5873,   144,   32,    5203,  2327,   27}, 
    {5874,   144,   32,    5203,  2327,   27}, 
    {5875,   144,   32,    5203,  2327,   27}, 
    {5876,   144,   32,    5207,  2322,   27}, 
    {5877,   144,   32,    5207,  2322,   27}, 
    {5878,   144,   32,    5207,  2323,   26}, 
    {5879,   144,   32,    5207,  2323,   26}, 
    {5203,  2327,   27,    5874,   145,   30},
    {5207,  2322, -255,    5875,   145,   30},
    {5207,  2323, -255,    5876,   145,   30},

////fire dungeon
//enterance
    {5827,  1502,    0,    2922,  3406,    8},
    {5828,  1502,   -1,    2923,  3406,    9},
    {5829,  1502,    2,    2924,  3406,    7},
    {2922,  3405,    7,    5827,  1501,    0},
    {2923,  3405,    6,    5828,  1501,    0},
    {2924,  3405,    7,    5829,  1501,    1},
//lvl1 - t2a exit
    {5790,  1415,   39,    5758,  2907,   15},
    {5790,  1416,   40,    5758,  2908,   15},
    {5790,  1417,   38,    5758,  2909,   15},
    {5757,  2907,   15,    5789,  1415,   42},
    {5757,  2908,   14,    5789,  1416,   39},
    {5757,  2909,   15,    5789,  1417,   38},
//lvl1 - lvl2
    {5786,  1335,  -13,    5701,  1318,    8},
    {5787,  1335,  -13,    5702,  1318,    8},
    {5788,  1335,  -13,    5703,  1318,    8},
    {5701,  1319,   13,    5786,  1336,   -8},
    {5702,  1319,   13,    5787,  1336,   -8},
    {5703,  1319,   13,    5788,  1336,   -8},

////volcano shop teleporter
    {1653,  2963,    0,    1671,  2981,    0},
    {1677,  2987,    0,    1675,  2987,   20},
    
////bucs den underground
//enterance
    {2674,  2242,    2,    2677,  2242,  -20},
    {2676,  2242,  -18,    2675,  2242,    2},
    {2676,  2242,  -18,    2675,  2242,    2},
//exit
    {2649,  2195,  -14,    2648,  2193,    4},
    {2669,  2072,  -19,    2669,  2072,    5},
    {2669,  2073,  -19,    2669,  2073,    5},

////britain sewer
//enterance
    {6031,  1499,   35,    1490,  1640,   24},
    {6031,  1501,   36,    1490,  1642,   24},
    {1491,  1640,   24,    6032,  1499,   31},
    {1491,  1642,   24,    6032,  1501,   31},
//lvl1 - cave
    {6140,  1431,    4,    6137,  1408,    2},
    {6141,  1431,    4,    6138,  1408,    2},
    {6137,  1409,    2,    6140,  1432,    4},
    {6138,  1409,    2,    6141,  1432,    4},
//cave - t2a exit
    {6126,  1410,   15,    6074,  3333,    2},
    {6127,  1410,   15,    6075,  3333,    2},    
    {6074,  3332,    4,    6126,  1409,   13},
    {6075,  3332,    4,    6127,  1409,   13},

////minoc cave
//enterance
    {2399,   198,    0,    6087,  3675,   17},
    {2400,   198,    0,    6087,  3676,   18},
//exit to t2a
    {6086,  3675,   15,    2399,   199,    0},
    {6086,  3676,   16,    2400,   199,    0},

////vesper graveyard
//enterance
    {2776,   894,  -23,    5685,   386,    1},
    {2776,   895,  -23,    5685,   387,    2},
    {5686,   386,    2,    2777,   894,  -23},
    {5686,   387,    2,    2777,   895,  -23},
//cave - t2a graveyard
    {5658,   423,    8,    5697,  3659,    2},
    {5697,  3660,   -5,    5658,   424,    0}, 

////trinsic cave
//enterance
    {1628,  3320,    0,    5899,  1409,   41},
    {1629,  3320,    0,    5900,  1409,   39}, 
    {5898,  1411,   38,    1628,  3321,    0},
    {5899,  1411,   43,    1628,  3321,    0},
    {5900,  1411,   42,    1629,  3321,    0},
//lvl1 - lvl2
    {5918,  1410,  -29,    5962,  1407,   57},
    {5918,  1411,  -29,    5962,  1408,   56},
    {5918,  1412,  -29,    5962,  1409,   56},
    {5961,  1407,   59,    5917,  1410,  -27},
    {5961,  1408,   59,    5917,  1411,  -27},
    {5961,  1409,   59,    5917,  1412,  -27},
//lvl2 - west t2a
    {6025,  1344,  -26,    5138,  3664,   31},
    {6025,  1345,  -25,    5138,  3665,   32},
    {6025,  1346,  -25,    5138,  3666,   32},
    {5137,  3664,   27,    6024,  1345,  -25},
    {5137,  3665,   31,    6024,  1346,  -25},
//lvl2 - delucia
    {6005,  1378,    0,    5151,  4062,   37},
    {6005,  1379,    2,    5151,  4063,   37},
    {6005,  1380,    1,    5151,  4064,   37},
    {5150,  4062,   38,    6004,  1378,    1},
    {5150,  4063,   38,    6004,  1379,   -1},
    
////terathan keep
//enterance
    {5426,  3122, -74,    5341,  1601,    0},
    {5341,  1601,   0,    5426,  3121,  -65},

////spirituality shrine
    {1592,  2489,   17,    1600,  2489,   10},
    {1600,  2489,   10,    1592,  2490,   17},
    {1600,  2490,   10,    1592,  2490,   17}
};

function CreateTeleporters()
  print ("Creating Teleporters...");
  if(GetGlobalProperty("SystemTeleportersCreated") == 1)
    print ("Teleporters already created...");
    return;
  endif
  foreach tele in teleporters
    var fromx := tele[1];
    var fromy := tele[2];
    var fromz := tele[3];
    var tox := tele[4];
    var toy := tele[5];
    var toz := tele[6];
    var teleporter := CreateItemAtLocation(fromx, fromy, fromz, "systemteleporter", 1, "britannia");
    if(teleporter)
      teleporter.graphic := 3948;
      SetObjProperty(teleporter, "DestX", tox);
      SetObjProperty(teleporter, "DestY", toy);
      SetObjProperty(teleporter, "DestZ", toz);
      
    endif
  endforeach
  SetGlobalProperty("SystemTeleportersCreated", 1);
  print ("Teleporters successfully created!!!");
endfunction
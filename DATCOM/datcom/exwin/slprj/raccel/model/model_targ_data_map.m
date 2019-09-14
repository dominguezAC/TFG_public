  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtP)
    ;%
      section.nData     = 171;
      section.data(171)  = dumData; %prealloc
      
	  ;% rtP.DiscreteWindGustModel_Gx
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.DiscreteWindGustModel_Gy
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.DiscreteWindGustModel_Gz
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.DrydenWindTurbulenceModelContinuousqr_L_high
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtP.AerodynamicForcesandMoments_S
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtP.AerodynamicForcesandMoments_S_irg2e3bjgp
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtP.AerodynamicForcesandMoments_S_haf3wauqag
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtP.DrydenWindTurbulenceModelContinuousqr_Seed
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtP.DrydenWindTurbulenceModelContinuousqr_T_on
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 11;
	
	  ;% rtP.WhiteNoise_Ts
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 12;
	
	  ;% rtP.DrydenWindTurbulenceModelContinuousqr_TurbProb
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 13;
	
	  ;% rtP.uDOFEulerAngles_Vm_0
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 14;
	
	  ;% rtP.DrydenWindTurbulenceModelContinuousqr_W20
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 17;
	
	  ;% rtP.WindShearModel_W_20
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 18;
	
	  ;% rtP.DrydenWindTurbulenceModelContinuousqr_Wdeg
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 19;
	
	  ;% rtP.WindShearModel_Wdeg
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 20;
	
	  ;% rtP.DrydenWindTurbulenceModelContinuousqr_Wingspan
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 21;
	
	  ;% rtP.AerodynamicForcesandMoments_b
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 22;
	
	  ;% rtP.AerodynamicForcesandMoments_b_a2pcrfjg54
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 23;
	
	  ;% rtP.AerodynamicForcesandMoments_b_efeekaqk2w
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 24;
	
	  ;% rtP.AerodynamicForcesandMoments_cbar
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 25;
	
	  ;% rtP.AerodynamicForcesandMoments_cbar_h4kwacm43q
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 26;
	
	  ;% rtP.AerodynamicForcesandMoments_cbar_miyvp11bgo
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 27;
	
	  ;% rtP.Distanceintogustx_d_m
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 28;
	
	  ;% rtP.Distanceintogusty_d_m
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 29;
	
	  ;% rtP.Distanceintogustz_d_m
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 30;
	
	  ;% rtP.DiscreteWindGustModel_d_m
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 31;
	
	  ;% rtP.uDOFEulerAngles_eul_0
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 34;
	
	  ;% rtP.uDOFEulerAngles_inertia
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 37;
	
	  ;% rtP.uDOFEulerAngles_mass_0
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 46;
	
	  ;% rtP.uDOFEulerAngles_pm_0
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 47;
	
	  ;% rtP.WhiteNoise_pwr
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 50;
	
	  ;% rtP.DiscreteWindGustModel_t_0
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 54;
	
	  ;% rtP.DiscreteWindGustModel_v_m
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 55;
	
	  ;% rtP.uDOFEulerAngles_xme_0
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 58;
	
	  ;% rtP.x_Y0
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 61;
	
	  ;% rtP.DistanceintoGustxLimitedtogustlengthd_IC
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 62;
	
	  ;% rtP.DistanceintoGustxLimitedtogustlengthd_LowerSat
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 63;
	
	  ;% rtP.pgw_Y0
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 64;
	
	  ;% rtP.Constant1_Value
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 65;
	
	  ;% rtP.Constant2_Value
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 66;
	
	  ;% rtP.Constant3_Value
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 67;
	
	  ;% rtP.pgw_p_IC
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 68;
	
	  ;% rtP.qgw_Y0
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 69;
	
	  ;% rtP.qgw_p_IC
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 70;
	
	  ;% rtP.pi4_Gain
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 71;
	
	  ;% rtP.rgw_Y0
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 72;
	
	  ;% rtP.rgw_p_IC
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 73;
	
	  ;% rtP.pi3_Gain
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 74;
	
	  ;% rtP.ugw_Y0
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 75;
	
	  ;% rtP.upi_Gain
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 76;
	
	  ;% rtP.ug_p_IC
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 77;
	
	  ;% rtP.vgw_Y0
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 78;
	
	  ;% rtP.upi_Gain_gy2nvc1rod
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 79;
	
	  ;% rtP.vg_p1_IC
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 80;
	
	  ;% rtP.vgw_p2_IC
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 81;
	
	  ;% rtP.sqrt3_Gain
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 82;
	
	  ;% rtP.wgw_Y0
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 83;
	
	  ;% rtP.upi_Gain_cv3kqumzgv
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 84;
	
	  ;% rtP.Constant_Value
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 85;
	
	  ;% rtP.wg_p1_IC
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 86;
	
	  ;% rtP.wg_p2_IC
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 87;
	
	  ;% rtP.Gain_Gain
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 88;
	
	  ;% rtP.max_height_low_Value
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 89;
	
	  ;% rtP.min_height_high_Value
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 90;
	
	  ;% rtP.Gain_Gain_hwyillaq5v
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 91;
	
	  ;% rtP.max_height_low_Value_lykhpozz3y
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 92;
	
	  ;% rtP.min_height_high_Value_f0iqsahu4c
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 93;
	
	  ;% rtP.Constant_Value_d1htqtqh1y
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 94;
	
	  ;% rtP.phithetapsi_WrappedStateUpperValue
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 98;
	
	  ;% rtP.phithetapsi_WrappedStateLowerValue
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 99;
	
	  ;% rtP.SeaLevelTemperature_Value
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 100;
	
	  ;% rtP.Limitaltitudetotroposhere_UpperSat
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 101;
	
	  ;% rtP.Limitaltitudetotroposhere_LowerSat
	  section.data(74).logicalSrcIdx = 73;
	  section.data(74).dtTransOffset = 102;
	
	  ;% rtP.LapseRate_Gain
	  section.data(75).logicalSrcIdx = 74;
	  section.data(75).dtTransOffset = 103;
	
	  ;% rtP.uT0_Gain
	  section.data(76).logicalSrcIdx = 75;
	  section.data(76).dtTransOffset = 104;
	
	  ;% rtP.Constant_Value_d2f1ederhe
	  section.data(77).logicalSrcIdx = 76;
	  section.data(77).dtTransOffset = 105;
	
	  ;% rtP.AltitudeofTroposphere_Value
	  section.data(78).logicalSrcIdx = 77;
	  section.data(78).dtTransOffset = 106;
	
	  ;% rtP.LimitaltitudetoStratosphere_UpperSat
	  section.data(79).logicalSrcIdx = 78;
	  section.data(79).dtTransOffset = 107;
	
	  ;% rtP.LimitaltitudetoStratosphere_LowerSat
	  section.data(80).logicalSrcIdx = 79;
	  section.data(80).dtTransOffset = 108;
	
	  ;% rtP.gR_Gain
	  section.data(81).logicalSrcIdx = 80;
	  section.data(81).dtTransOffset = 109;
	
	  ;% rtP.rho0_Gain
	  section.data(82).logicalSrcIdx = 81;
	  section.data(82).dtTransOffset = 110;
	
	  ;% rtP.gammaR_Gain
	  section.data(83).logicalSrcIdx = 82;
	  section.data(83).dtTransOffset = 111;
	
	  ;% rtP.u_Value
	  section.data(84).logicalSrcIdx = 83;
	  section.data(84).dtTransOffset = 112;
	
	  ;% rtP.LimitFunction10ftto1000ft_UpperSat
	  section.data(85).logicalSrcIdx = 84;
	  section.data(85).dtTransOffset = 113;
	
	  ;% rtP.LimitFunction10ftto1000ft_LowerSat
	  section.data(86).logicalSrcIdx = 85;
	  section.data(86).dtTransOffset = 114;
	
	  ;% rtP.Lw_Gain
	  section.data(87).logicalSrcIdx = 86;
	  section.data(87).dtTransOffset = 115;
	
	  ;% rtP.sigma_wg_Gain
	  section.data(88).logicalSrcIdx = 87;
	  section.data(88).dtTransOffset = 116;
	
	  ;% rtP.PreLookUpIndexSearchaltitude_BreakpointsData
	  section.data(89).logicalSrcIdx = 88;
	  section.data(89).dtTransOffset = 117;
	
	  ;% rtP.PreLookUpIndexSearchprobofexceed_BreakpointsData
	  section.data(90).logicalSrcIdx = 89;
	  section.data(90).dtTransOffset = 129;
	
	  ;% rtP.MediumHighAltitudeIntensity_Table
	  section.data(91).logicalSrcIdx = 90;
	  section.data(91).dtTransOffset = 136;
	
	  ;% rtP.WhiteNoise_Mean
	  section.data(92).logicalSrcIdx = 91;
	  section.data(92).dtTransOffset = 220;
	
	  ;% rtP.WhiteNoise_StdDev
	  section.data(93).logicalSrcIdx = 92;
	  section.data(93).dtTransOffset = 221;
	
	  ;% rtP.LimitHeighth1000ft_UpperSat
	  section.data(94).logicalSrcIdx = 93;
	  section.data(94).dtTransOffset = 222;
	
	  ;% rtP.LimitHeighth1000ft_LowerSat
	  section.data(95).logicalSrcIdx = 94;
	  section.data(95).dtTransOffset = 223;
	
	  ;% rtP.Lv_Gain
	  section.data(96).logicalSrcIdx = 95;
	  section.data(96).dtTransOffset = 224;
	
	  ;% rtP.uftinf_UpperSat
	  section.data(97).logicalSrcIdx = 96;
	  section.data(97).dtTransOffset = 225;
	
	  ;% rtP.uftinf_LowerSat
	  section.data(98).logicalSrcIdx = 97;
	  section.data(98).dtTransOffset = 226;
	
	  ;% rtP.hz0_Gain
	  section.data(99).logicalSrcIdx = 98;
	  section.data(99).dtTransOffset = 227;
	
	  ;% rtP.ref_heightz0_Value
	  section.data(100).logicalSrcIdx = 99;
	  section.data(100).dtTransOffset = 228;
	
	  ;% rtP.Wdeg1_Value
	  section.data(101).logicalSrcIdx = 100;
	  section.data(101).dtTransOffset = 229;
	
	  ;% rtP.Constant2_Value_nvqbu4imhl
	  section.data(102).logicalSrcIdx = 101;
	  section.data(102).dtTransOffset = 230;
	
	  ;% rtP.Constant_Value_bjnypp3rh0
	  section.data(103).logicalSrcIdx = 102;
	  section.data(103).dtTransOffset = 239;
	
	  ;% rtP.Constant1_Value_e4n53dlcvq
	  section.data(104).logicalSrcIdx = 103;
	  section.data(104).dtTransOffset = 248;
	
	  ;% rtP.Constant_Value_m5ji3jk5ts
	  section.data(105).logicalSrcIdx = 104;
	  section.data(105).dtTransOffset = 249;
	
	  ;% rtP.Constant2_Value_pnmq1xmzoy
	  section.data(106).logicalSrcIdx = 105;
	  section.data(106).dtTransOffset = 250;
	
	  ;% rtP.Constant4_Value
	  section.data(107).logicalSrcIdx = 106;
	  section.data(107).dtTransOffset = 251;
	
	  ;% rtP.Constant3_Value_py4vyr01be
	  section.data(108).logicalSrcIdx = 107;
	  section.data(108).dtTransOffset = 252;
	
	  ;% rtP.u2rhoV2_Gain
	  section.data(109).logicalSrcIdx = 108;
	  section.data(109).dtTransOffset = 253;
	
	  ;% rtP.alpha_BreakpointsData
	  section.data(110).logicalSrcIdx = 109;
	  section.data(110).dtTransOffset = 254;
	
	  ;% rtP.Mach_BreakpointsData
	  section.data(111).logicalSrcIdx = 110;
	  section.data(111).dtTransOffset = 264;
	
	  ;% rtP.altitude_BreakpointsData
	  section.data(112).logicalSrcIdx = 111;
	  section.data(112).dtTransOffset = 268;
	
	  ;% rtP.CD_Table
	  section.data(113).logicalSrcIdx = 112;
	  section.data(113).dtTransOffset = 276;
	
	  ;% rtP.CYb_Table
	  section.data(114).logicalSrcIdx = 113;
	  section.data(114).dtTransOffset = 596;
	
	  ;% rtP.CL_Table
	  section.data(115).logicalSrcIdx = 114;
	  section.data(115).dtTransOffset = 916;
	
	  ;% rtP.coefAdjust_Gain
	  section.data(116).logicalSrcIdx = 115;
	  section.data(116).dtTransOffset = 1236;
	
	  ;% rtP.Constant1_Value_bllnswxjjm
	  section.data(117).logicalSrcIdx = 116;
	  section.data(117).dtTransOffset = 1239;
	
	  ;% rtP.Constant_Value_gvjlparkjc
	  section.data(118).logicalSrcIdx = 117;
	  section.data(118).dtTransOffset = 1240;
	
	  ;% rtP.Constant2_Value_ewaxby0wwz
	  section.data(119).logicalSrcIdx = 118;
	  section.data(119).dtTransOffset = 1241;
	
	  ;% rtP.Constant4_Value_jw4i4dtkq1
	  section.data(120).logicalSrcIdx = 119;
	  section.data(120).dtTransOffset = 1242;
	
	  ;% rtP.Constant3_Value_aowcwxcrv4
	  section.data(121).logicalSrcIdx = 120;
	  section.data(121).dtTransOffset = 1243;
	
	  ;% rtP.zero3_Value
	  section.data(122).logicalSrcIdx = 121;
	  section.data(122).dtTransOffset = 1244;
	
	  ;% rtP.Clb_Table
	  section.data(123).logicalSrcIdx = 122;
	  section.data(123).dtTransOffset = 1247;
	
	  ;% rtP.Cm_Table
	  section.data(124).logicalSrcIdx = 123;
	  section.data(124).dtTransOffset = 1567;
	
	  ;% rtP.Cnb_Table
	  section.data(125).logicalSrcIdx = 124;
	  section.data(125).dtTransOffset = 1887;
	
	  ;% rtP.Constant1_Value_dkxf1g33uf
	  section.data(126).logicalSrcIdx = 125;
	  section.data(126).dtTransOffset = 2207;
	
	  ;% rtP.Constant_Value_n2pgnoma5y
	  section.data(127).logicalSrcIdx = 126;
	  section.data(127).dtTransOffset = 2208;
	
	  ;% rtP.Constant2_Value_a1organdvp
	  section.data(128).logicalSrcIdx = 127;
	  section.data(128).dtTransOffset = 2209;
	
	  ;% rtP.Constant4_Value_mowtqh2zd2
	  section.data(129).logicalSrcIdx = 128;
	  section.data(129).dtTransOffset = 2210;
	
	  ;% rtP.Constant3_Value_n2x4c42jkt
	  section.data(130).logicalSrcIdx = 129;
	  section.data(130).dtTransOffset = 2211;
	
	  ;% rtP.zero_Value
	  section.data(131).logicalSrcIdx = 130;
	  section.data(131).dtTransOffset = 2212;
	
	  ;% rtP.CYp_Table
	  section.data(132).logicalSrcIdx = 131;
	  section.data(132).dtTransOffset = 2213;
	
	  ;% rtP.u_Value_fiovphx5x3
	  section.data(133).logicalSrcIdx = 132;
	  section.data(133).dtTransOffset = 2533;
	
	  ;% rtP.Constant_Value_lnzqsdhb20
	  section.data(134).logicalSrcIdx = 133;
	  section.data(134).dtTransOffset = 2534;
	
	  ;% rtP.u_Value_aardduo22y
	  section.data(135).logicalSrcIdx = 134;
	  section.data(135).dtTransOffset = 2535;
	
	  ;% rtP.Constant_Value_lqmbfph4ah
	  section.data(136).logicalSrcIdx = 135;
	  section.data(136).dtTransOffset = 2536;
	
	  ;% rtP.CLad_Table
	  section.data(137).logicalSrcIdx = 136;
	  section.data(137).dtTransOffset = 2537;
	
	  ;% rtP.CLq_Table
	  section.data(138).logicalSrcIdx = 137;
	  section.data(138).dtTransOffset = 2857;
	
	  ;% rtP.Clp_Table
	  section.data(139).logicalSrcIdx = 138;
	  section.data(139).dtTransOffset = 3177;
	
	  ;% rtP.Clr_Table
	  section.data(140).logicalSrcIdx = 139;
	  section.data(140).dtTransOffset = 3497;
	
	  ;% rtP.Cmq_Table
	  section.data(141).logicalSrcIdx = 140;
	  section.data(141).dtTransOffset = 3817;
	
	  ;% rtP.Cmad_Table
	  section.data(142).logicalSrcIdx = 141;
	  section.data(142).dtTransOffset = 4137;
	
	  ;% rtP.Cnp_Table
	  section.data(143).logicalSrcIdx = 142;
	  section.data(143).dtTransOffset = 4457;
	
	  ;% rtP.Cnr_Table
	  section.data(144).logicalSrcIdx = 143;
	  section.data(144).dtTransOffset = 4777;
	
	  ;% rtP.Gain1_Gain
	  section.data(145).logicalSrcIdx = 144;
	  section.data(145).dtTransOffset = 5097;
	
	  ;% rtP.u_Value_axd001kf0t
	  section.data(146).logicalSrcIdx = 145;
	  section.data(146).dtTransOffset = 5103;
	
	  ;% rtP.coefAdjust_Gain_d5gkknnahd
	  section.data(147).logicalSrcIdx = 146;
	  section.data(147).dtTransOffset = 5104;
	
	  ;% rtP.Constant1_Value_kfsbs5wuhz
	  section.data(148).logicalSrcIdx = 147;
	  section.data(148).dtTransOffset = 5107;
	
	  ;% rtP.Constant_Value_feqzr4eans
	  section.data(149).logicalSrcIdx = 148;
	  section.data(149).dtTransOffset = 5108;
	
	  ;% rtP.Constant2_Value_agtqtjm4z1
	  section.data(150).logicalSrcIdx = 149;
	  section.data(150).dtTransOffset = 5109;
	
	  ;% rtP.Constant4_Value_pnrru5m0fs
	  section.data(151).logicalSrcIdx = 150;
	  section.data(151).dtTransOffset = 5110;
	
	  ;% rtP.Constant3_Value_lnoybacp11
	  section.data(152).logicalSrcIdx = 151;
	  section.data(152).dtTransOffset = 5111;
	
	  ;% rtP.zero1_Value
	  section.data(153).logicalSrcIdx = 152;
	  section.data(153).dtTransOffset = 5112;
	
	  ;% rtP.Constant2_Value_pjsapbkri4
	  section.data(154).logicalSrcIdx = 153;
	  section.data(154).dtTransOffset = 5115;
	
	  ;% rtP.coefAdjust_Gain_i4hwujqkud
	  section.data(155).logicalSrcIdx = 154;
	  section.data(155).dtTransOffset = 5121;
	
	  ;% rtP.Constant1_Value_az5chewn2m
	  section.data(156).logicalSrcIdx = 155;
	  section.data(156).dtTransOffset = 5124;
	
	  ;% rtP.Constant_Value_cbj5azvbu2
	  section.data(157).logicalSrcIdx = 156;
	  section.data(157).dtTransOffset = 5127;
	
	  ;% rtP.Moments_Value
	  section.data(158).logicalSrcIdx = 157;
	  section.data(158).dtTransOffset = 5130;
	
	  ;% rtP.Constant1_Value_cy5z4hcsl3
	  section.data(159).logicalSrcIdx = 158;
	  section.data(159).dtTransOffset = 5133;
	
	  ;% rtP.Constant_Value_ea5rkpodns
	  section.data(160).logicalSrcIdx = 159;
	  section.data(160).dtTransOffset = 5134;
	
	  ;% rtP.Constant2_Value_epbnzx0ky0
	  section.data(161).logicalSrcIdx = 160;
	  section.data(161).dtTransOffset = 5135;
	
	  ;% rtP.Constant4_Value_atc41zi2ir
	  section.data(162).logicalSrcIdx = 161;
	  section.data(162).dtTransOffset = 5136;
	
	  ;% rtP.Constant3_Value_jmheminny5
	  section.data(163).logicalSrcIdx = 162;
	  section.data(163).dtTransOffset = 5137;
	
	  ;% rtP.Constant1_Value_ndgxvb4zwb
	  section.data(164).logicalSrcIdx = 163;
	  section.data(164).dtTransOffset = 5138;
	
	  ;% rtP.Constant_Value_m1jhswm2a4
	  section.data(165).logicalSrcIdx = 164;
	  section.data(165).dtTransOffset = 5139;
	
	  ;% rtP.Constant2_Value_ogp3xqdtea
	  section.data(166).logicalSrcIdx = 165;
	  section.data(166).dtTransOffset = 5140;
	
	  ;% rtP.Constant4_Value_gcn5uwst2a
	  section.data(167).logicalSrcIdx = 166;
	  section.data(167).dtTransOffset = 5141;
	
	  ;% rtP.Constant3_Value_oqhlderhny
	  section.data(168).logicalSrcIdx = 167;
	  section.data(168).dtTransOffset = 5142;
	
	  ;% rtP.ThrustX_tableData
	  section.data(169).logicalSrcIdx = 168;
	  section.data(169).dtTransOffset = 5143;
	
	  ;% rtP.ThrustX_bp01Data
	  section.data(170).logicalSrcIdx = 169;
	  section.data(170).dtTransOffset = 5150;
	
	  ;% rtP.TyTz_Value
	  section.data(171).logicalSrcIdx = 170;
	  section.data(171).dtTransOffset = 5157;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% rtP.MediumHighAltitudeIntensity_maxIndex
	  section.data(1).logicalSrcIdx = 171;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.CD_dimSize
	  section.data(2).logicalSrcIdx = 172;
	  section.data(2).dtTransOffset = 2;
	
	  ;% rtP.CYb_dimSize
	  section.data(3).logicalSrcIdx = 173;
	  section.data(3).dtTransOffset = 5;
	
	  ;% rtP.CL_dimSize
	  section.data(4).logicalSrcIdx = 174;
	  section.data(4).dtTransOffset = 8;
	
	  ;% rtP.Clb_dimSize
	  section.data(5).logicalSrcIdx = 175;
	  section.data(5).dtTransOffset = 11;
	
	  ;% rtP.Cm_dimSize
	  section.data(6).logicalSrcIdx = 176;
	  section.data(6).dtTransOffset = 14;
	
	  ;% rtP.Cnb_dimSize
	  section.data(7).logicalSrcIdx = 177;
	  section.data(7).dtTransOffset = 17;
	
	  ;% rtP.CYp_dimSize
	  section.data(8).logicalSrcIdx = 178;
	  section.data(8).dtTransOffset = 20;
	
	  ;% rtP.CLad_dimSize
	  section.data(9).logicalSrcIdx = 179;
	  section.data(9).dtTransOffset = 23;
	
	  ;% rtP.CLq_dimSize
	  section.data(10).logicalSrcIdx = 180;
	  section.data(10).dtTransOffset = 26;
	
	  ;% rtP.Clp_dimSize
	  section.data(11).logicalSrcIdx = 181;
	  section.data(11).dtTransOffset = 29;
	
	  ;% rtP.Clr_dimSize
	  section.data(12).logicalSrcIdx = 182;
	  section.data(12).dtTransOffset = 32;
	
	  ;% rtP.Cmq_dimSize
	  section.data(13).logicalSrcIdx = 183;
	  section.data(13).dtTransOffset = 35;
	
	  ;% rtP.Cmad_dimSize
	  section.data(14).logicalSrcIdx = 184;
	  section.data(14).dtTransOffset = 38;
	
	  ;% rtP.Cnp_dimSize
	  section.data(15).logicalSrcIdx = 185;
	  section.data(15).dtTransOffset = 41;
	
	  ;% rtP.Cnr_dimSize
	  section.data(16).logicalSrcIdx = 186;
	  section.data(16).dtTransOffset = 44;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtP.fieqmbp0km.x_Y0
	  section.data(1).logicalSrcIdx = 187;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.fieqmbp0km.DistanceintoGustxLimitedtogustlengthd_IC
	  section.data(2).logicalSrcIdx = 188;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.fieqmbp0km.DistanceintoGustxLimitedtogustlengthd_LowerSat
	  section.data(3).logicalSrcIdx = 189;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtP.jgkdl5lezan.x_Y0
	  section.data(1).logicalSrcIdx = 190;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.jgkdl5lezan.DistanceintoGustxLimitedtogustlengthd_IC
	  section.data(2).logicalSrcIdx = 191;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.jgkdl5lezan.DistanceintoGustxLimitedtogustlengthd_LowerSat
	  section.data(3).logicalSrcIdx = 192;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 6;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtB)
    ;%
      section.nData     = 284;
      section.data(284)  = dumData; %prealloc
      
	  ;% rtB.dzs1soumuc
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.islqk3d2pc
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 3;
	
	  ;% rtB.nliw1cuyp4
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 6;
	
	  ;% rtB.fnmpprt3rb
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 9;
	
	  ;% rtB.n2gibbklhx
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 12;
	
	  ;% rtB.mycisuihic
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 21;
	
	  ;% rtB.bxute4gwb3
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 30;
	
	  ;% rtB.ks25o2ves0
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 33;
	
	  ;% rtB.ktmthpvsav
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 36;
	
	  ;% rtB.g0uv0nbjrn
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 37;
	
	  ;% rtB.hwshuznfry
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 38;
	
	  ;% rtB.gyvp0nr1ic
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 39;
	
	  ;% rtB.fpjovq1wmk
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 40;
	
	  ;% rtB.ewye0ur1dg
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 41;
	
	  ;% rtB.fkybzc33mt
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 42;
	
	  ;% rtB.b21axyrc0y
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 43;
	
	  ;% rtB.h0chbuggcq
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 44;
	
	  ;% rtB.odqt54fd3r
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 45;
	
	  ;% rtB.iwsvf4t0jp
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 46;
	
	  ;% rtB.ijj1ba05uy
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 47;
	
	  ;% rtB.ney5ntjpte
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 48;
	
	  ;% rtB.dx5g5jxszw
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 49;
	
	  ;% rtB.k3tn4bbpdh
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 52;
	
	  ;% rtB.gtav0xroqm
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 55;
	
	  ;% rtB.pg1uquivv5
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 58;
	
	  ;% rtB.optvc153u0
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 59;
	
	  ;% rtB.ie5ujfwk1t
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 60;
	
	  ;% rtB.in1jikpuyp
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 61;
	
	  ;% rtB.lweizeobnn
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 62;
	
	  ;% rtB.k1qm14mokl
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 64;
	
	  ;% rtB.pba0balycr
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 65;
	
	  ;% rtB.m4ioj5ifig
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 66;
	
	  ;% rtB.bsrwvm2oyt
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 67;
	
	  ;% rtB.iw50kb54tc
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 68;
	
	  ;% rtB.c0yzmpobn3
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 72;
	
	  ;% rtB.apsbh2a4ml
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 76;
	
	  ;% rtB.p5dpqn0t0m
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 77;
	
	  ;% rtB.fkpy3ggxgw
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 78;
	
	  ;% rtB.lklogdjcfo
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 79;
	
	  ;% rtB.bdqq1m4fup
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 80;
	
	  ;% rtB.mdfbuebpbf
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 82;
	
	  ;% rtB.i5asy1ic4l
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 85;
	
	  ;% rtB.jayfpbovsb
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 88;
	
	  ;% rtB.etz0t5ppwo
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 89;
	
	  ;% rtB.htbwrd0zad
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 90;
	
	  ;% rtB.kbexovbmwl
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 91;
	
	  ;% rtB.pwozxpkovz
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 92;
	
	  ;% rtB.hnfbrhdub5
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 93;
	
	  ;% rtB.na2v1kjbp5
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 96;
	
	  ;% rtB.gtph1dwlhy
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 99;
	
	  ;% rtB.cis0kg11y4
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 102;
	
	  ;% rtB.nzoyizvn0g
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 105;
	
	  ;% rtB.pnx4iii03b
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 108;
	
	  ;% rtB.mrsrezbuqk
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 111;
	
	  ;% rtB.jjyzm5cerc
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 120;
	
	  ;% rtB.k4efj0wbom
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 123;
	
	  ;% rtB.abq35lnui2
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 124;
	
	  ;% rtB.pwkjv4lxgw
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 125;
	
	  ;% rtB.fhjxy5zb5a
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 126;
	
	  ;% rtB.aami4huvyy
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 127;
	
	  ;% rtB.bdaejykwvz
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 128;
	
	  ;% rtB.o54r3adnq1
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 129;
	
	  ;% rtB.bwcottfiut
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 132;
	
	  ;% rtB.j55tg2sijl
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 141;
	
	  ;% rtB.dsk4lj4maj
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 144;
	
	  ;% rtB.e4f4cr5zbc
	  section.data(66).logicalSrcIdx = 65;
	  section.data(66).dtTransOffset = 153;
	
	  ;% rtB.a5q0gsfmw5
	  section.data(67).logicalSrcIdx = 66;
	  section.data(67).dtTransOffset = 156;
	
	  ;% rtB.jymybd53fk
	  section.data(68).logicalSrcIdx = 67;
	  section.data(68).dtTransOffset = 165;
	
	  ;% rtB.fwuesmfvmw
	  section.data(69).logicalSrcIdx = 68;
	  section.data(69).dtTransOffset = 174;
	
	  ;% rtB.ee4hwukkci
	  section.data(70).logicalSrcIdx = 69;
	  section.data(70).dtTransOffset = 177;
	
	  ;% rtB.llhvjlhy3a
	  section.data(71).logicalSrcIdx = 70;
	  section.data(71).dtTransOffset = 178;
	
	  ;% rtB.no1ukhz2or
	  section.data(72).logicalSrcIdx = 71;
	  section.data(72).dtTransOffset = 179;
	
	  ;% rtB.lw3rqy0i2p
	  section.data(73).logicalSrcIdx = 72;
	  section.data(73).dtTransOffset = 180;
	
	  ;% rtB.gzwn4wvhu5
	  section.data(74).logicalSrcIdx = 73;
	  section.data(74).dtTransOffset = 181;
	
	  ;% rtB.ltux4bsueq
	  section.data(75).logicalSrcIdx = 74;
	  section.data(75).dtTransOffset = 182;
	
	  ;% rtB.lcss4j1rsb
	  section.data(76).logicalSrcIdx = 75;
	  section.data(76).dtTransOffset = 183;
	
	  ;% rtB.oovkaz423b
	  section.data(77).logicalSrcIdx = 76;
	  section.data(77).dtTransOffset = 184;
	
	  ;% rtB.cdvlb44lh3
	  section.data(78).logicalSrcIdx = 77;
	  section.data(78).dtTransOffset = 185;
	
	  ;% rtB.ewv4vlunrf
	  section.data(79).logicalSrcIdx = 78;
	  section.data(79).dtTransOffset = 186;
	
	  ;% rtB.o402scsdlq
	  section.data(80).logicalSrcIdx = 79;
	  section.data(80).dtTransOffset = 187;
	
	  ;% rtB.dsfnt4ckk0
	  section.data(81).logicalSrcIdx = 80;
	  section.data(81).dtTransOffset = 188;
	
	  ;% rtB.deyrabdk0p
	  section.data(82).logicalSrcIdx = 81;
	  section.data(82).dtTransOffset = 189;
	
	  ;% rtB.ew4bp2hsh4
	  section.data(83).logicalSrcIdx = 82;
	  section.data(83).dtTransOffset = 190;
	
	  ;% rtB.fghbljyvca
	  section.data(84).logicalSrcIdx = 83;
	  section.data(84).dtTransOffset = 191;
	
	  ;% rtB.n0yew4kwsy
	  section.data(85).logicalSrcIdx = 84;
	  section.data(85).dtTransOffset = 192;
	
	  ;% rtB.l1czztlzln
	  section.data(86).logicalSrcIdx = 85;
	  section.data(86).dtTransOffset = 193;
	
	  ;% rtB.kn3vx2wdwp
	  section.data(87).logicalSrcIdx = 86;
	  section.data(87).dtTransOffset = 194;
	
	  ;% rtB.iv0iqohpcq
	  section.data(88).logicalSrcIdx = 87;
	  section.data(88).dtTransOffset = 195;
	
	  ;% rtB.nqhs2mtakg
	  section.data(89).logicalSrcIdx = 88;
	  section.data(89).dtTransOffset = 196;
	
	  ;% rtB.mddzbq4nmv
	  section.data(90).logicalSrcIdx = 89;
	  section.data(90).dtTransOffset = 197;
	
	  ;% rtB.c5nk0hb2bd
	  section.data(91).logicalSrcIdx = 90;
	  section.data(91).dtTransOffset = 198;
	
	  ;% rtB.dkjk3aymc3
	  section.data(92).logicalSrcIdx = 91;
	  section.data(92).dtTransOffset = 199;
	
	  ;% rtB.k4vi5txoqv
	  section.data(93).logicalSrcIdx = 92;
	  section.data(93).dtTransOffset = 200;
	
	  ;% rtB.jeow23fizp
	  section.data(94).logicalSrcIdx = 93;
	  section.data(94).dtTransOffset = 201;
	
	  ;% rtB.g4ixw2ju0a
	  section.data(95).logicalSrcIdx = 94;
	  section.data(95).dtTransOffset = 204;
	
	  ;% rtB.clsso41xlk
	  section.data(96).logicalSrcIdx = 95;
	  section.data(96).dtTransOffset = 207;
	
	  ;% rtB.diwxdnf4dg
	  section.data(97).logicalSrcIdx = 96;
	  section.data(97).dtTransOffset = 216;
	
	  ;% rtB.m43khr12tv
	  section.data(98).logicalSrcIdx = 97;
	  section.data(98).dtTransOffset = 219;
	
	  ;% rtB.oq23oeketq
	  section.data(99).logicalSrcIdx = 98;
	  section.data(99).dtTransOffset = 222;
	
	  ;% rtB.ambckm20k4
	  section.data(100).logicalSrcIdx = 99;
	  section.data(100).dtTransOffset = 223;
	
	  ;% rtB.if2tkmjk5a
	  section.data(101).logicalSrcIdx = 100;
	  section.data(101).dtTransOffset = 224;
	
	  ;% rtB.jhnqdtipvy
	  section.data(102).logicalSrcIdx = 101;
	  section.data(102).dtTransOffset = 225;
	
	  ;% rtB.mmnv4q2o2x
	  section.data(103).logicalSrcIdx = 102;
	  section.data(103).dtTransOffset = 226;
	
	  ;% rtB.dr2gm5cuey
	  section.data(104).logicalSrcIdx = 103;
	  section.data(104).dtTransOffset = 227;
	
	  ;% rtB.fhapciging
	  section.data(105).logicalSrcIdx = 104;
	  section.data(105).dtTransOffset = 228;
	
	  ;% rtB.b4ff4mfmin
	  section.data(106).logicalSrcIdx = 105;
	  section.data(106).dtTransOffset = 231;
	
	  ;% rtB.huplh2ovz1
	  section.data(107).logicalSrcIdx = 106;
	  section.data(107).dtTransOffset = 232;
	
	  ;% rtB.dtay24vczs
	  section.data(108).logicalSrcIdx = 107;
	  section.data(108).dtTransOffset = 233;
	
	  ;% rtB.flfgzaiek3
	  section.data(109).logicalSrcIdx = 108;
	  section.data(109).dtTransOffset = 234;
	
	  ;% rtB.p0xy05kpqr
	  section.data(110).logicalSrcIdx = 109;
	  section.data(110).dtTransOffset = 235;
	
	  ;% rtB.kuokdfsr0b
	  section.data(111).logicalSrcIdx = 110;
	  section.data(111).dtTransOffset = 236;
	
	  ;% rtB.muyb1go0zp
	  section.data(112).logicalSrcIdx = 111;
	  section.data(112).dtTransOffset = 239;
	
	  ;% rtB.haarcsgs3r
	  section.data(113).logicalSrcIdx = 112;
	  section.data(113).dtTransOffset = 242;
	
	  ;% rtB.gb1h1tviap
	  section.data(114).logicalSrcIdx = 113;
	  section.data(114).dtTransOffset = 245;
	
	  ;% rtB.bltg1ofzuh
	  section.data(115).logicalSrcIdx = 114;
	  section.data(115).dtTransOffset = 248;
	
	  ;% rtB.mddt1rvp3v
	  section.data(116).logicalSrcIdx = 115;
	  section.data(116).dtTransOffset = 257;
	
	  ;% rtB.mwuv02g011
	  section.data(117).logicalSrcIdx = 116;
	  section.data(117).dtTransOffset = 266;
	
	  ;% rtB.d3um45fosu
	  section.data(118).logicalSrcIdx = 117;
	  section.data(118).dtTransOffset = 267;
	
	  ;% rtB.nw0lnpybdj
	  section.data(119).logicalSrcIdx = 118;
	  section.data(119).dtTransOffset = 268;
	
	  ;% rtB.fy3whyspik
	  section.data(120).logicalSrcIdx = 119;
	  section.data(120).dtTransOffset = 270;
	
	  ;% rtB.nveqijgo2a
	  section.data(121).logicalSrcIdx = 120;
	  section.data(121).dtTransOffset = 271;
	
	  ;% rtB.ewoylkmqxc
	  section.data(122).logicalSrcIdx = 121;
	  section.data(122).dtTransOffset = 272;
	
	  ;% rtB.dhy5sl1c4z
	  section.data(123).logicalSrcIdx = 122;
	  section.data(123).dtTransOffset = 281;
	
	  ;% rtB.cdrl4nzwfz
	  section.data(124).logicalSrcIdx = 123;
	  section.data(124).dtTransOffset = 282;
	
	  ;% rtB.h1rmkjrkmq
	  section.data(125).logicalSrcIdx = 124;
	  section.data(125).dtTransOffset = 283;
	
	  ;% rtB.kp24wjtakv
	  section.data(126).logicalSrcIdx = 125;
	  section.data(126).dtTransOffset = 284;
	
	  ;% rtB.hmgj5nsbpj
	  section.data(127).logicalSrcIdx = 126;
	  section.data(127).dtTransOffset = 285;
	
	  ;% rtB.poq3sq0itr
	  section.data(128).logicalSrcIdx = 127;
	  section.data(128).dtTransOffset = 288;
	
	  ;% rtB.fui5djlzoo
	  section.data(129).logicalSrcIdx = 128;
	  section.data(129).dtTransOffset = 291;
	
	  ;% rtB.kkxd3tikbn
	  section.data(130).logicalSrcIdx = 129;
	  section.data(130).dtTransOffset = 292;
	
	  ;% rtB.hmi4l5cfx0
	  section.data(131).logicalSrcIdx = 130;
	  section.data(131).dtTransOffset = 293;
	
	  ;% rtB.dtsa0qdpmd
	  section.data(132).logicalSrcIdx = 131;
	  section.data(132).dtTransOffset = 294;
	
	  ;% rtB.n1pgu24wwz
	  section.data(133).logicalSrcIdx = 132;
	  section.data(133).dtTransOffset = 295;
	
	  ;% rtB.adbita3g4i
	  section.data(134).logicalSrcIdx = 133;
	  section.data(134).dtTransOffset = 296;
	
	  ;% rtB.gb0mdchddg
	  section.data(135).logicalSrcIdx = 134;
	  section.data(135).dtTransOffset = 297;
	
	  ;% rtB.gspj4vw5g2
	  section.data(136).logicalSrcIdx = 135;
	  section.data(136).dtTransOffset = 298;
	
	  ;% rtB.i12dfhokz1
	  section.data(137).logicalSrcIdx = 136;
	  section.data(137).dtTransOffset = 299;
	
	  ;% rtB.aokxroo1bz
	  section.data(138).logicalSrcIdx = 137;
	  section.data(138).dtTransOffset = 301;
	
	  ;% rtB.hyd1pi2bmq
	  section.data(139).logicalSrcIdx = 138;
	  section.data(139).dtTransOffset = 302;
	
	  ;% rtB.csyxoinipa
	  section.data(140).logicalSrcIdx = 139;
	  section.data(140).dtTransOffset = 303;
	
	  ;% rtB.adcuqjpjfk
	  section.data(141).logicalSrcIdx = 140;
	  section.data(141).dtTransOffset = 304;
	
	  ;% rtB.dfv5zlgscv
	  section.data(142).logicalSrcIdx = 141;
	  section.data(142).dtTransOffset = 305;
	
	  ;% rtB.m0mnsmhzee
	  section.data(143).logicalSrcIdx = 142;
	  section.data(143).dtTransOffset = 306;
	
	  ;% rtB.hqz5grr5x5
	  section.data(144).logicalSrcIdx = 143;
	  section.data(144).dtTransOffset = 307;
	
	  ;% rtB.nvp5xdnq4m
	  section.data(145).logicalSrcIdx = 144;
	  section.data(145).dtTransOffset = 308;
	
	  ;% rtB.aoguormswf
	  section.data(146).logicalSrcIdx = 145;
	  section.data(146).dtTransOffset = 309;
	
	  ;% rtB.ku2mt5oq34
	  section.data(147).logicalSrcIdx = 146;
	  section.data(147).dtTransOffset = 311;
	
	  ;% rtB.ok4uvdpxny
	  section.data(148).logicalSrcIdx = 147;
	  section.data(148).dtTransOffset = 312;
	
	  ;% rtB.mvem5vfcmh
	  section.data(149).logicalSrcIdx = 148;
	  section.data(149).dtTransOffset = 318;
	
	  ;% rtB.mqdmh5qxvd
	  section.data(150).logicalSrcIdx = 149;
	  section.data(150).dtTransOffset = 319;
	
	  ;% rtB.jranmezdtp
	  section.data(151).logicalSrcIdx = 150;
	  section.data(151).dtTransOffset = 320;
	
	  ;% rtB.elj1og2hw2
	  section.data(152).logicalSrcIdx = 151;
	  section.data(152).dtTransOffset = 321;
	
	  ;% rtB.oykwjbf0l2
	  section.data(153).logicalSrcIdx = 152;
	  section.data(153).dtTransOffset = 322;
	
	  ;% rtB.mjvjidnmqy
	  section.data(154).logicalSrcIdx = 153;
	  section.data(154).dtTransOffset = 328;
	
	  ;% rtB.d1znscnd2p
	  section.data(155).logicalSrcIdx = 154;
	  section.data(155).dtTransOffset = 331;
	
	  ;% rtB.bkeumodt1t
	  section.data(156).logicalSrcIdx = 155;
	  section.data(156).dtTransOffset = 334;
	
	  ;% rtB.mjh3qtkwwe
	  section.data(157).logicalSrcIdx = 156;
	  section.data(157).dtTransOffset = 343;
	
	  ;% rtB.kl54abxyyo
	  section.data(158).logicalSrcIdx = 157;
	  section.data(158).dtTransOffset = 346;
	
	  ;% rtB.na33cozjmh
	  section.data(159).logicalSrcIdx = 158;
	  section.data(159).dtTransOffset = 349;
	
	  ;% rtB.gy531db5ab
	  section.data(160).logicalSrcIdx = 159;
	  section.data(160).dtTransOffset = 350;
	
	  ;% rtB.n00wehaagy
	  section.data(161).logicalSrcIdx = 160;
	  section.data(161).dtTransOffset = 351;
	
	  ;% rtB.hsc0hjfp4c
	  section.data(162).logicalSrcIdx = 161;
	  section.data(162).dtTransOffset = 352;
	
	  ;% rtB.ju4uigrkf5
	  section.data(163).logicalSrcIdx = 162;
	  section.data(163).dtTransOffset = 353;
	
	  ;% rtB.ikfhliwvmn
	  section.data(164).logicalSrcIdx = 163;
	  section.data(164).dtTransOffset = 354;
	
	  ;% rtB.chj2lnrtdr
	  section.data(165).logicalSrcIdx = 164;
	  section.data(165).dtTransOffset = 355;
	
	  ;% rtB.d53l1o1puh
	  section.data(166).logicalSrcIdx = 165;
	  section.data(166).dtTransOffset = 358;
	
	  ;% rtB.khtpgpvqjl
	  section.data(167).logicalSrcIdx = 166;
	  section.data(167).dtTransOffset = 361;
	
	  ;% rtB.fkghwm5gsz
	  section.data(168).logicalSrcIdx = 167;
	  section.data(168).dtTransOffset = 364;
	
	  ;% rtB.cugpw2oaop
	  section.data(169).logicalSrcIdx = 168;
	  section.data(169).dtTransOffset = 367;
	
	  ;% rtB.f5hluqgotp
	  section.data(170).logicalSrcIdx = 169;
	  section.data(170).dtTransOffset = 370;
	
	  ;% rtB.hg2rkm0b0a
	  section.data(171).logicalSrcIdx = 170;
	  section.data(171).dtTransOffset = 373;
	
	  ;% rtB.eas3pz0d31
	  section.data(172).logicalSrcIdx = 171;
	  section.data(172).dtTransOffset = 374;
	
	  ;% rtB.jewko3ql0j
	  section.data(173).logicalSrcIdx = 172;
	  section.data(173).dtTransOffset = 377;
	
	  ;% rtB.boldxgnyxd
	  section.data(174).logicalSrcIdx = 173;
	  section.data(174).dtTransOffset = 380;
	
	  ;% rtB.ogjmkxrtzk
	  section.data(175).logicalSrcIdx = 174;
	  section.data(175).dtTransOffset = 383;
	
	  ;% rtB.acnxtf0njr
	  section.data(176).logicalSrcIdx = 175;
	  section.data(176).dtTransOffset = 384;
	
	  ;% rtB.apvxa3vvr5
	  section.data(177).logicalSrcIdx = 176;
	  section.data(177).dtTransOffset = 385;
	
	  ;% rtB.o5is4gwrz1
	  section.data(178).logicalSrcIdx = 177;
	  section.data(178).dtTransOffset = 386;
	
	  ;% rtB.a2r2bsx5op
	  section.data(179).logicalSrcIdx = 178;
	  section.data(179).dtTransOffset = 387;
	
	  ;% rtB.iknur005un
	  section.data(180).logicalSrcIdx = 179;
	  section.data(180).dtTransOffset = 388;
	
	  ;% rtB.ltisnx0tk2
	  section.data(181).logicalSrcIdx = 180;
	  section.data(181).dtTransOffset = 389;
	
	  ;% rtB.hnflxg3oyc
	  section.data(182).logicalSrcIdx = 181;
	  section.data(182).dtTransOffset = 392;
	
	  ;% rtB.ahalic5glf
	  section.data(183).logicalSrcIdx = 182;
	  section.data(183).dtTransOffset = 395;
	
	  ;% rtB.gbi1feu30l
	  section.data(184).logicalSrcIdx = 183;
	  section.data(184).dtTransOffset = 398;
	
	  ;% rtB.lsixin3gz1
	  section.data(185).logicalSrcIdx = 184;
	  section.data(185).dtTransOffset = 401;
	
	  ;% rtB.bhsoq03twv
	  section.data(186).logicalSrcIdx = 185;
	  section.data(186).dtTransOffset = 404;
	
	  ;% rtB.ph3xybkpn3
	  section.data(187).logicalSrcIdx = 186;
	  section.data(187).dtTransOffset = 407;
	
	  ;% rtB.ooprpnnz1m
	  section.data(188).logicalSrcIdx = 187;
	  section.data(188).dtTransOffset = 410;
	
	  ;% rtB.hlwx1xld4v
	  section.data(189).logicalSrcIdx = 188;
	  section.data(189).dtTransOffset = 419;
	
	  ;% rtB.iglnjbiqey
	  section.data(190).logicalSrcIdx = 189;
	  section.data(190).dtTransOffset = 422;
	
	  ;% rtB.iylzbmkgfi
	  section.data(191).logicalSrcIdx = 190;
	  section.data(191).dtTransOffset = 431;
	
	  ;% rtB.ntlxpgwfz1
	  section.data(192).logicalSrcIdx = 191;
	  section.data(192).dtTransOffset = 440;
	
	  ;% rtB.er0wsgu0uz
	  section.data(193).logicalSrcIdx = 192;
	  section.data(193).dtTransOffset = 443;
	
	  ;% rtB.nqqzwty3zs
	  section.data(194).logicalSrcIdx = 193;
	  section.data(194).dtTransOffset = 452;
	
	  ;% rtB.cavyfym52n
	  section.data(195).logicalSrcIdx = 194;
	  section.data(195).dtTransOffset = 461;
	
	  ;% rtB.lhmph3qfyb
	  section.data(196).logicalSrcIdx = 195;
	  section.data(196).dtTransOffset = 464;
	
	  ;% rtB.jhpnbmxx5n
	  section.data(197).logicalSrcIdx = 196;
	  section.data(197).dtTransOffset = 467;
	
	  ;% rtB.cp032iv5kb
	  section.data(198).logicalSrcIdx = 197;
	  section.data(198).dtTransOffset = 470;
	
	  ;% rtB.p5lvunc4gi
	  section.data(199).logicalSrcIdx = 198;
	  section.data(199).dtTransOffset = 471;
	
	  ;% rtB.f3tffkcsn4
	  section.data(200).logicalSrcIdx = 199;
	  section.data(200).dtTransOffset = 474;
	
	  ;% rtB.pytois5kxe
	  section.data(201).logicalSrcIdx = 200;
	  section.data(201).dtTransOffset = 477;
	
	  ;% rtB.dj5opchr3c
	  section.data(202).logicalSrcIdx = 201;
	  section.data(202).dtTransOffset = 478;
	
	  ;% rtB.hjgda4lsay
	  section.data(203).logicalSrcIdx = 202;
	  section.data(203).dtTransOffset = 479;
	
	  ;% rtB.pf1sahzmz5
	  section.data(204).logicalSrcIdx = 203;
	  section.data(204).dtTransOffset = 480;
	
	  ;% rtB.j0zjfcbwwv
	  section.data(205).logicalSrcIdx = 204;
	  section.data(205).dtTransOffset = 481;
	
	  ;% rtB.hogqcx5gkm
	  section.data(206).logicalSrcIdx = 205;
	  section.data(206).dtTransOffset = 482;
	
	  ;% rtB.pqmqi1ih0x
	  section.data(207).logicalSrcIdx = 206;
	  section.data(207).dtTransOffset = 483;
	
	  ;% rtB.orhueszosr
	  section.data(208).logicalSrcIdx = 207;
	  section.data(208).dtTransOffset = 486;
	
	  ;% rtB.iwoj22k0me
	  section.data(209).logicalSrcIdx = 208;
	  section.data(209).dtTransOffset = 489;
	
	  ;% rtB.hwhw1vlr4q
	  section.data(210).logicalSrcIdx = 209;
	  section.data(210).dtTransOffset = 491;
	
	  ;% rtB.bhyqpcr3sv
	  section.data(211).logicalSrcIdx = 210;
	  section.data(211).dtTransOffset = 493;
	
	  ;% rtB.pfqekgkkul
	  section.data(212).logicalSrcIdx = 211;
	  section.data(212).dtTransOffset = 496;
	
	  ;% rtB.m0012em1dm
	  section.data(213).logicalSrcIdx = 212;
	  section.data(213).dtTransOffset = 499;
	
	  ;% rtB.edfjbabvwj
	  section.data(214).logicalSrcIdx = 213;
	  section.data(214).dtTransOffset = 502;
	
	  ;% rtB.h5wwlzhkjq
	  section.data(215).logicalSrcIdx = 214;
	  section.data(215).dtTransOffset = 503;
	
	  ;% rtB.ocqymszfcg
	  section.data(216).logicalSrcIdx = 215;
	  section.data(216).dtTransOffset = 504;
	
	  ;% rtB.mt2kbdde1u
	  section.data(217).logicalSrcIdx = 216;
	  section.data(217).dtTransOffset = 507;
	
	  ;% rtB.hlywm50421
	  section.data(218).logicalSrcIdx = 217;
	  section.data(218).dtTransOffset = 509;
	
	  ;% rtB.bkjlztmjbx
	  section.data(219).logicalSrcIdx = 218;
	  section.data(219).dtTransOffset = 511;
	
	  ;% rtB.g2ol2zgsoe
	  section.data(220).logicalSrcIdx = 219;
	  section.data(220).dtTransOffset = 514;
	
	  ;% rtB.lez1v1wcmt
	  section.data(221).logicalSrcIdx = 220;
	  section.data(221).dtTransOffset = 517;
	
	  ;% rtB.jtve1smewc
	  section.data(222).logicalSrcIdx = 221;
	  section.data(222).dtTransOffset = 519;
	
	  ;% rtB.fwd0zho2dx
	  section.data(223).logicalSrcIdx = 222;
	  section.data(223).dtTransOffset = 521;
	
	  ;% rtB.pqzxc0jwxr
	  section.data(224).logicalSrcIdx = 223;
	  section.data(224).dtTransOffset = 524;
	
	  ;% rtB.n2ablemxjo
	  section.data(225).logicalSrcIdx = 224;
	  section.data(225).dtTransOffset = 527;
	
	  ;% rtB.lgsfqf2gng
	  section.data(226).logicalSrcIdx = 225;
	  section.data(226).dtTransOffset = 530;
	
	  ;% rtB.obpi4pygmr
	  section.data(227).logicalSrcIdx = 226;
	  section.data(227).dtTransOffset = 531;
	
	  ;% rtB.bvoynuyjfa
	  section.data(228).logicalSrcIdx = 227;
	  section.data(228).dtTransOffset = 532;
	
	  ;% rtB.p4yyhd2kug
	  section.data(229).logicalSrcIdx = 228;
	  section.data(229).dtTransOffset = 535;
	
	  ;% rtB.bv3tfatqfb
	  section.data(230).logicalSrcIdx = 229;
	  section.data(230).dtTransOffset = 537;
	
	  ;% rtB.eqg4nglih0
	  section.data(231).logicalSrcIdx = 230;
	  section.data(231).dtTransOffset = 539;
	
	  ;% rtB.gynkhxmcfk
	  section.data(232).logicalSrcIdx = 231;
	  section.data(232).dtTransOffset = 542;
	
	  ;% rtB.clyzpdujo2
	  section.data(233).logicalSrcIdx = 232;
	  section.data(233).dtTransOffset = 545;
	
	  ;% rtB.nmo53ueedw
	  section.data(234).logicalSrcIdx = 233;
	  section.data(234).dtTransOffset = 547;
	
	  ;% rtB.pcg1z1bmhq
	  section.data(235).logicalSrcIdx = 234;
	  section.data(235).dtTransOffset = 549;
	
	  ;% rtB.lq0mfgsqfo
	  section.data(236).logicalSrcIdx = 235;
	  section.data(236).dtTransOffset = 551;
	
	  ;% rtB.adrc4dh4xz
	  section.data(237).logicalSrcIdx = 236;
	  section.data(237).dtTransOffset = 553;
	
	  ;% rtB.maka3wnq5n
	  section.data(238).logicalSrcIdx = 237;
	  section.data(238).dtTransOffset = 555;
	
	  ;% rtB.b4p0x5sch3
	  section.data(239).logicalSrcIdx = 238;
	  section.data(239).dtTransOffset = 557;
	
	  ;% rtB.cayuqvyp2b
	  section.data(240).logicalSrcIdx = 239;
	  section.data(240).dtTransOffset = 558;
	
	  ;% rtB.on0w3ltr4i
	  section.data(241).logicalSrcIdx = 240;
	  section.data(241).dtTransOffset = 560;
	
	  ;% rtB.gunypeaovn
	  section.data(242).logicalSrcIdx = 241;
	  section.data(242).dtTransOffset = 562;
	
	  ;% rtB.jokuewxh0b
	  section.data(243).logicalSrcIdx = 242;
	  section.data(243).dtTransOffset = 564;
	
	  ;% rtB.pxqxqpltfm
	  section.data(244).logicalSrcIdx = 243;
	  section.data(244).dtTransOffset = 566;
	
	  ;% rtB.fmyvw4bkag
	  section.data(245).logicalSrcIdx = 244;
	  section.data(245).dtTransOffset = 568;
	
	  ;% rtB.ivknkgdhps
	  section.data(246).logicalSrcIdx = 245;
	  section.data(246).dtTransOffset = 570;
	
	  ;% rtB.mmtxyw115q
	  section.data(247).logicalSrcIdx = 246;
	  section.data(247).dtTransOffset = 572;
	
	  ;% rtB.oprrh1lrfg
	  section.data(248).logicalSrcIdx = 247;
	  section.data(248).dtTransOffset = 574;
	
	  ;% rtB.ealls03ntz
	  section.data(249).logicalSrcIdx = 248;
	  section.data(249).dtTransOffset = 576;
	
	  ;% rtB.cmdkij32ho
	  section.data(250).logicalSrcIdx = 249;
	  section.data(250).dtTransOffset = 578;
	
	  ;% rtB.gdx0qpo30e
	  section.data(251).logicalSrcIdx = 250;
	  section.data(251).dtTransOffset = 580;
	
	  ;% rtB.bqywvwxy2u
	  section.data(252).logicalSrcIdx = 251;
	  section.data(252).dtTransOffset = 582;
	
	  ;% rtB.md41g5fldt
	  section.data(253).logicalSrcIdx = 252;
	  section.data(253).dtTransOffset = 584;
	
	  ;% rtB.ke0ksubsuu
	  section.data(254).logicalSrcIdx = 253;
	  section.data(254).dtTransOffset = 586;
	
	  ;% rtB.fmytsanjo2
	  section.data(255).logicalSrcIdx = 254;
	  section.data(255).dtTransOffset = 588;
	
	  ;% rtB.joo0gvrcnf
	  section.data(256).logicalSrcIdx = 255;
	  section.data(256).dtTransOffset = 590;
	
	  ;% rtB.h2tissrusk
	  section.data(257).logicalSrcIdx = 256;
	  section.data(257).dtTransOffset = 592;
	
	  ;% rtB.beaa0ietcq
	  section.data(258).logicalSrcIdx = 257;
	  section.data(258).dtTransOffset = 594;
	
	  ;% rtB.bph5jjv2nj
	  section.data(259).logicalSrcIdx = 258;
	  section.data(259).dtTransOffset = 596;
	
	  ;% rtB.jj1mymkjgz
	  section.data(260).logicalSrcIdx = 259;
	  section.data(260).dtTransOffset = 598;
	
	  ;% rtB.etpdtmtrnf
	  section.data(261).logicalSrcIdx = 260;
	  section.data(261).dtTransOffset = 600;
	
	  ;% rtB.igi43iu4gc
	  section.data(262).logicalSrcIdx = 261;
	  section.data(262).dtTransOffset = 602;
	
	  ;% rtB.iihgtnzfrf
	  section.data(263).logicalSrcIdx = 262;
	  section.data(263).dtTransOffset = 604;
	
	  ;% rtB.j5rmezwb0e
	  section.data(264).logicalSrcIdx = 263;
	  section.data(264).dtTransOffset = 606;
	
	  ;% rtB.fg2kqgg3ek
	  section.data(265).logicalSrcIdx = 264;
	  section.data(265).dtTransOffset = 608;
	
	  ;% rtB.fjkfysvnh3
	  section.data(266).logicalSrcIdx = 265;
	  section.data(266).dtTransOffset = 610;
	
	  ;% rtB.fjfsy0b0jg
	  section.data(267).logicalSrcIdx = 266;
	  section.data(267).dtTransOffset = 612;
	
	  ;% rtB.b2e3g5hpyo
	  section.data(268).logicalSrcIdx = 267;
	  section.data(268).dtTransOffset = 613;
	
	  ;% rtB.lazwt4wtdp
	  section.data(269).logicalSrcIdx = 268;
	  section.data(269).dtTransOffset = 615;
	
	  ;% rtB.b1khfo1ad3
	  section.data(270).logicalSrcIdx = 269;
	  section.data(270).dtTransOffset = 617;
	
	  ;% rtB.fr0lgjauqr
	  section.data(271).logicalSrcIdx = 270;
	  section.data(271).dtTransOffset = 619;
	
	  ;% rtB.dt4hmrvy0i
	  section.data(272).logicalSrcIdx = 271;
	  section.data(272).dtTransOffset = 621;
	
	  ;% rtB.oum15dzd35
	  section.data(273).logicalSrcIdx = 272;
	  section.data(273).dtTransOffset = 622;
	
	  ;% rtB.buysvvpcb4
	  section.data(274).logicalSrcIdx = 273;
	  section.data(274).dtTransOffset = 624;
	
	  ;% rtB.o1xsnq5r4j
	  section.data(275).logicalSrcIdx = 274;
	  section.data(275).dtTransOffset = 625;
	
	  ;% rtB.cfsazsff55
	  section.data(276).logicalSrcIdx = 275;
	  section.data(276).dtTransOffset = 626;
	
	  ;% rtB.e40fmoqlfe
	  section.data(277).logicalSrcIdx = 276;
	  section.data(277).dtTransOffset = 628;
	
	  ;% rtB.gzz55ngh4d
	  section.data(278).logicalSrcIdx = 277;
	  section.data(278).dtTransOffset = 630;
	
	  ;% rtB.of5hnba1qi
	  section.data(279).logicalSrcIdx = 278;
	  section.data(279).dtTransOffset = 632;
	
	  ;% rtB.cr4rspe1f1
	  section.data(280).logicalSrcIdx = 279;
	  section.data(280).dtTransOffset = 634;
	
	  ;% rtB.mfxy45ba4c
	  section.data(281).logicalSrcIdx = 280;
	  section.data(281).dtTransOffset = 636;
	
	  ;% rtB.p3bdm41p1x
	  section.data(282).logicalSrcIdx = 281;
	  section.data(282).dtTransOffset = 638;
	
	  ;% rtB.hbksfryqsi
	  section.data(283).logicalSrcIdx = 282;
	  section.data(283).dtTransOffset = 639;
	
	  ;% rtB.juld5yz3om
	  section.data(284).logicalSrcIdx = 283;
	  section.data(284).dtTransOffset = 641;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtB.guh13rgg0c
	  section.data(1).logicalSrcIdx = 284;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.kjfzsflye3
	  section.data(2).logicalSrcIdx = 285;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtB.burumew3sb
	  section.data(1).logicalSrcIdx = 286;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.dpmiotlnvk
	  section.data(2).logicalSrcIdx = 287;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.kcp5vlmrhn
	  section.data(3).logicalSrcIdx = 288;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtB.b25nd1ut2t
	  section.data(1).logicalSrcIdx = 289;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.oeyxyxnkxg
	  section.data(2).logicalSrcIdx = 290;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtB.owpauozhbv
	  section.data(3).logicalSrcIdx = 291;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.fieqmbp0km.bkh4ie4vlq
	  section.data(1).logicalSrcIdx = 292;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.jgkdl5lezan.bkh4ie4vlq
	  section.data(1).logicalSrcIdx = 293;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(6) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 13;
    sectIdxOffset = 6;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtDW)
    ;%
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% rtDW.e5dwuk5zfi
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.lb14r5vg2a
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.j3aywkmo1f.LoggedData
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtDW.m0wkbsdvjm
	  section.data(1).logicalSrcIdx = 3;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.pfswjzddny
	  section.data(2).logicalSrcIdx = 4;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.bweuyeryhh
	  section.data(3).logicalSrcIdx = 5;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% rtDW.ltv3hasgw5
	  section.data(1).logicalSrcIdx = 6;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.g4kd5mgehq
	  section.data(2).logicalSrcIdx = 7;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.o2m0ho4ib0
	  section.data(3).logicalSrcIdx = 8;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.cgeqxzgrnv
	  section.data(4).logicalSrcIdx = 9;
	  section.data(4).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% rtDW.g4ktzwz3i1
	  section.data(1).logicalSrcIdx = 10;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.ofhki50iy1
	  section.data(2).logicalSrcIdx = 11;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.ifz1r4v4pr
	  section.data(3).logicalSrcIdx = 12;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.ia5fgrdrmk
	  section.data(4).logicalSrcIdx = 13;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.oqzl4vaurj
	  section.data(5).logicalSrcIdx = 14;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.jqsfntesyx
	  section.data(6).logicalSrcIdx = 15;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 28;
      section.data(28)  = dumData; %prealloc
      
	  ;% rtDW.nx5ne33bex
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.jusb02f5rj
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.nhbi5jh4go
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.ag2s0tuis0
	  section.data(4).logicalSrcIdx = 19;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.kpq2e44z2g
	  section.data(5).logicalSrcIdx = 20;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.amv55hlazd
	  section.data(6).logicalSrcIdx = 21;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.kpnxk2wxcb
	  section.data(7).logicalSrcIdx = 22;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.ir0jb20k33
	  section.data(8).logicalSrcIdx = 23;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtDW.cnovvjoyyp
	  section.data(9).logicalSrcIdx = 24;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtDW.pgykvwqmc3
	  section.data(10).logicalSrcIdx = 25;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtDW.ftwguoefpc
	  section.data(11).logicalSrcIdx = 26;
	  section.data(11).dtTransOffset = 10;
	
	  ;% rtDW.osdasmnnlg
	  section.data(12).logicalSrcIdx = 27;
	  section.data(12).dtTransOffset = 11;
	
	  ;% rtDW.kscxtxtsbw
	  section.data(13).logicalSrcIdx = 28;
	  section.data(13).dtTransOffset = 12;
	
	  ;% rtDW.feainkhr2c
	  section.data(14).logicalSrcIdx = 29;
	  section.data(14).dtTransOffset = 13;
	
	  ;% rtDW.lj1lobgjwr
	  section.data(15).logicalSrcIdx = 30;
	  section.data(15).dtTransOffset = 14;
	
	  ;% rtDW.gs4wlth0q0
	  section.data(16).logicalSrcIdx = 31;
	  section.data(16).dtTransOffset = 15;
	
	  ;% rtDW.pfnakgwhvn
	  section.data(17).logicalSrcIdx = 32;
	  section.data(17).dtTransOffset = 16;
	
	  ;% rtDW.ne00r4ogt0
	  section.data(18).logicalSrcIdx = 33;
	  section.data(18).dtTransOffset = 17;
	
	  ;% rtDW.jjjovfqaio
	  section.data(19).logicalSrcIdx = 34;
	  section.data(19).dtTransOffset = 18;
	
	  ;% rtDW.euk35lqnv1
	  section.data(20).logicalSrcIdx = 35;
	  section.data(20).dtTransOffset = 19;
	
	  ;% rtDW.ceqnsrmeb1
	  section.data(21).logicalSrcIdx = 36;
	  section.data(21).dtTransOffset = 20;
	
	  ;% rtDW.fg0n3tzsij
	  section.data(22).logicalSrcIdx = 37;
	  section.data(22).dtTransOffset = 21;
	
	  ;% rtDW.cjrmyujqju
	  section.data(23).logicalSrcIdx = 38;
	  section.data(23).dtTransOffset = 22;
	
	  ;% rtDW.ptevicn33b
	  section.data(24).logicalSrcIdx = 39;
	  section.data(24).dtTransOffset = 23;
	
	  ;% rtDW.iu54wjtvx2
	  section.data(25).logicalSrcIdx = 40;
	  section.data(25).dtTransOffset = 24;
	
	  ;% rtDW.ddqyu2zcpv
	  section.data(26).logicalSrcIdx = 41;
	  section.data(26).dtTransOffset = 25;
	
	  ;% rtDW.nfawadvxsq
	  section.data(27).logicalSrcIdx = 42;
	  section.data(27).dtTransOffset = 26;
	
	  ;% rtDW.pkkgwpmnt2
	  section.data(28).logicalSrcIdx = 43;
	  section.data(28).dtTransOffset = 27;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% rtDW.ek25wc14yf
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.ptxtk1nv30
	  section.data(2).logicalSrcIdx = 45;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.nhrxrmv3xz
	  section.data(3).logicalSrcIdx = 46;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.gjeq11lqni
	  section.data(4).logicalSrcIdx = 47;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.dtbuv1dhzu
	  section.data(5).logicalSrcIdx = 48;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtDW.dsenq15ybl
	  section.data(6).logicalSrcIdx = 49;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtDW.ekhaunodew
	  section.data(7).logicalSrcIdx = 50;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtDW.f3e4goswub
	  section.data(8).logicalSrcIdx = 51;
	  section.data(8).dtTransOffset = 7;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.fieqmbp0km.cztgqg1pxv
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.fieqmbp0km.lzpni3vohm
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.fieqmbp0km.hndz0ioosi
	  section.data(1).logicalSrcIdx = 54;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.jgkdl5lezan.cztgqg1pxv
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.jgkdl5lezan.lzpni3vohm
	  section.data(1).logicalSrcIdx = 56;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtDW.jgkdl5lezan.hndz0ioosi
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 444972961;
  targMap.checksum1 = 4146120540;
  targMap.checksum2 = 2950918377;
  targMap.checksum3 = 2309469585;


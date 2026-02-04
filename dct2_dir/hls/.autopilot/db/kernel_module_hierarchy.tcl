set ModuleHierarchy {[{
"Name" : "IDCT2","ID" : "0","Type" : "sequential",
"SubInsts" : [
	{"Name" : "grp_IDCT2_Pipeline_VITIS_LOOP_329_1_fu_184","ID" : "1","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_329_1","ID" : "2","Type" : "pipeline",
		"SubInsts" : [
		{"Name" : "call_ret1_IDCT2B2_fu_328","ID" : "3","Type" : "pipeline"},
		{"Name" : "grp_IDCT2B4_fu_334","ID" : "4","Type" : "pipeline",
				"SubInsts" : [
				{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "5","Type" : "pipeline"},]},
		{"Name" : "grp_IDCT2B8_fu_342","ID" : "6","Type" : "pipeline",
				"SubInsts" : [
				{"Name" : "grp_IDCT2B4_fu_92","ID" : "7","Type" : "pipeline",
					"SubInsts" : [
					{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "8","Type" : "pipeline"},]},]},
		{"Name" : "grp_IDCT2B16_fu_354","ID" : "9","Type" : "pipeline",
				"SubInsts" : [
				{"Name" : "grp_IDCT2B8_fu_164","ID" : "10","Type" : "pipeline",
					"SubInsts" : [
					{"Name" : "grp_IDCT2B4_fu_92","ID" : "11","Type" : "pipeline",
						"SubInsts" : [
						{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "12","Type" : "pipeline"},]},]},]},
		{"Name" : "grp_IDCT2B32_fu_374","ID" : "13","Type" : "pipeline",
				"SubInsts" : [
				{"Name" : "grp_IDCT2B16_fu_306","ID" : "14","Type" : "pipeline",
					"SubInsts" : [
					{"Name" : "grp_IDCT2B8_fu_164","ID" : "15","Type" : "pipeline",
						"SubInsts" : [
						{"Name" : "grp_IDCT2B4_fu_92","ID" : "16","Type" : "pipeline",
							"SubInsts" : [
							{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "17","Type" : "pipeline"},]},]},]},]},
		{"Name" : "grp_IDCT2B64_fu_410","ID" : "18","Type" : "pipeline",
				"SubInsts" : [
				{"Name" : "grp_IDCT2B32_fu_574","ID" : "19","Type" : "pipeline",
					"SubInsts" : [
					{"Name" : "grp_IDCT2B16_fu_306","ID" : "20","Type" : "pipeline",
						"SubInsts" : [
						{"Name" : "grp_IDCT2B8_fu_164","ID" : "21","Type" : "pipeline",
							"SubInsts" : [
							{"Name" : "grp_IDCT2B4_fu_92","ID" : "22","Type" : "pipeline",
								"SubInsts" : [
								{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "23","Type" : "pipeline"},]},]},]},]},]},]},]},]
}]}
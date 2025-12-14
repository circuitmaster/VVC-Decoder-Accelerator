set ModuleHierarchy {[{
"Name" : "IDCT2","ID" : "0","Type" : "pipeline",
"SubLoops" : [
	{"Name" : "VITIS_LOOP_324_1","ID" : "1","Type" : "pipeline",
	"SubInsts" : [
	{"Name" : "call_ret4_IDCT2B16_fu_260","ID" : "2","Type" : "pipeline",
			"SubInsts" : [
			{"Name" : "call_ret_IDCT2B8_fu_164","ID" : "3","Type" : "pipeline",
				"SubInsts" : [
				{"Name" : "call_ret_IDCT2B4_fu_92","ID" : "4","Type" : "pipeline",
					"SubInsts" : [
					{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "5","Type" : "pipeline"},]},]},]},
	{"Name" : "grp_IDCT2B32_fu_280","ID" : "6","Type" : "pipeline",
			"SubInsts" : [
			{"Name" : "call_ret_IDCT2B16_fu_306","ID" : "7","Type" : "pipeline",
				"SubInsts" : [
				{"Name" : "call_ret_IDCT2B8_fu_164","ID" : "8","Type" : "pipeline",
					"SubInsts" : [
					{"Name" : "call_ret_IDCT2B4_fu_92","ID" : "9","Type" : "pipeline",
						"SubInsts" : [
						{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "10","Type" : "pipeline"},]},]},]},]},
	{"Name" : "grp_IDCT2B64_fu_316","ID" : "11","Type" : "pipeline",
			"SubInsts" : [
			{"Name" : "grp_IDCT2B32_fu_260","ID" : "12","Type" : "pipeline",
				"SubInsts" : [
				{"Name" : "call_ret_IDCT2B16_fu_306","ID" : "13","Type" : "pipeline",
					"SubInsts" : [
					{"Name" : "call_ret_IDCT2B8_fu_164","ID" : "14","Type" : "pipeline",
						"SubInsts" : [
						{"Name" : "call_ret_IDCT2B4_fu_92","ID" : "15","Type" : "pipeline",
							"SubInsts" : [
							{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "16","Type" : "pipeline"},]},]},]},]},]},
	{"Name" : "call_ret5_IDCT2B4_fu_337","ID" : "17","Type" : "pipeline",
			"SubInsts" : [
			{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "18","Type" : "pipeline"},]},
	{"Name" : "call_ret_IDCT2B8_fu_345","ID" : "19","Type" : "pipeline",
			"SubInsts" : [
			{"Name" : "call_ret_IDCT2B4_fu_92","ID" : "20","Type" : "pipeline",
				"SubInsts" : [
				{"Name" : "call_ret_IDCT2B2_fu_50","ID" : "21","Type" : "pipeline"},]},]},
	{"Name" : "call_ret1_IDCT2B2_fu_357","ID" : "22","Type" : "pipeline"},]},]
}]}
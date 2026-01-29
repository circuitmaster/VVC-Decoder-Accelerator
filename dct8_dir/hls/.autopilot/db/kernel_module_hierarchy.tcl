set ModuleHierarchy {[{
"Name" : "IDCT8","ID" : "0","Type" : "sequential",
"SubLoops" : [
	{"Name" : "VITIS_LOOP_260_1","ID" : "1","Type" : "no",
	"SubInsts" : [
	{"Name" : "grp_IDCT8B8_fu_680","ID" : "2","Type" : "sequential",
			"SubInsts" : [
			{"Name" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158","ID" : "3","Type" : "sequential",
				"SubLoops" : [
				{"Name" : "VITIS_LOOP_21_1","ID" : "4","Type" : "pipeline"},]},]},
	{"Name" : "grp_IDCT8B16_fu_720","ID" : "5","Type" : "sequential",
			"SubInsts" : [
			{"Name" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258","ID" : "6","Type" : "sequential",
				"SubLoops" : [
				{"Name" : "VITIS_LOOP_47_1","ID" : "7","Type" : "pipeline"},]},]},
	{"Name" : "grp_IDCT8B32_fu_792","ID" : "8","Type" : "sequential",
			"SubInsts" : [
			{"Name" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452","ID" : "9","Type" : "sequential",
				"SubLoops" : [
				{"Name" : "VITIS_LOOP_73_1","ID" : "10","Type" : "pipeline"},]},]},]},]
}]}
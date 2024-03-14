workspace "Sources"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	startproject "FEditor"

outputdir = "%{wks.location}/../Bin/"
objoutdir = "%{wks.location}/../Bin-Int/"
dependdir = "%{wks.location}/../Dependencies/"

include "FTools"
include "FWindow"
include "FEditorUI"

include "FEditor"
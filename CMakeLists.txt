cmake_minimum_required(VERSION 3.23)
project(CPPContainer)

set(CMAKE_CXX_STANDARD 20)
include_directories("DS")
add_executable(CPPContainer main.cpp DS/LazyPropogationInSegmentTree.h DS/IntervalMap.h DS/ST_Persistency.h DS/LongestPrefixMatching.h "DS/ReverseDNSLookUp.h" "DS/ForwardDNSLookupCache.h" "DS/BinaryIndexedTreeFenwick.h" "DS/BITRangeUpdate.h" "DS/SuffixArrayIntroduction.h" "DS/UkkonenSuffixTree.h" "DS/QuickSort.h" "DS/SpanTest.h" "DS/SMathModule.cppm" "DS/RandomInRange.h" "DS/OptionalTest.h" "DS/roman.cppm" "DS/to_roman.cpp" "DS/from_roman.cpp" "DS/romanTest.h" "DS/TruckLoadBox.h" "DS/Polymorphism/pBox.h" "DS/Polymorphism/pCan.h" "DS/Polymorphism/pCarton.h" "DS/Polymorphism/pToughPack.h" "DS/Polymorphism/pVessel.h")

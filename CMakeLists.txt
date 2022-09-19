cmake_minimum_required(VERSION 3.23)
project(CPPContainer)

set(CMAKE_CXX_STANDARD 17)
include_directories("DS")
add_executable(CPPContainer main.cpp DS/LazyPropogationInSegmentTree.h DS/IntervalMap.h DS/ST_Persistency.h DS/LongestPrefixMatching.h "DS/ReverseDNSLookUp.h" "DS/ForwardDNSLookupCache.h" "DS/BinaryIndexedTreeFenwick.h" "DS/BITRangeUpdate.h" "DS/SuffixArrayIntroduction.h" "DS/UkkonenSuffixTree.h")

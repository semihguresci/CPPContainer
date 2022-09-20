#include <iostream>

#include "IntervalMap.h"
#include "MatrixCommonElement.h"
#include "ExpressionTree.h"
#include "GenericLLC.h"
#include "XORLinkListSET1.h"

#include "SegmentTree.h"
#include "RangeMinimumQuery.h"
#include "LazyPropogationInSegmentTree.h"
#include "ST_Persistency.h"
#include "LongestPrefixMatching.h"
#include <ReverseDNSLookUp.h>
#include  <ForwardDNSLookupCache.h>
#include <BinaryIndexedTreeFenwick.h>
#include  <D2BinaryIndexTree.h>
#include <BITRangeUpdate.h>
#include <SuffixArrayIntroduction.h>
#include <QuickSort.h>
#include <SpanTest.h>
#include <RandomInRange.h>
#include <OptionalTest.h>
#include <romanTest.h>
#include <TruckLoadBox.h>

//#include <UkkonenSuffixTree.h>
int main()
{
    
    STSumofGivenRange* sgr = new STSumofGivenRange();
    sgr->Run();
    delete sgr;


    LongestPrefixMatching::TrieTest *tt = new LongestPrefixMatching::TrieTest();
    tt->Run();
    delete tt;
    
    ReverseDNSLookup::TrieTest *rdtest = new ReverseDNSLookup::TrieTest();
    rdtest->Run();
    delete rdtest;

    std::cout << std:: endl;

    ForwardDNSLookupCache::trieTest* fdtest = new ForwardDNSLookupCache::trieTest();
    fdtest->Run();
    delete fdtest;

    BinartIndexTreeStructure::BinaryIndexedTreeTest* bitt = new BinartIndexTreeStructure::BinaryIndexedTreeTest();
    bitt->Run();
    delete bitt;
  

    TwoDimansionalBITFenwickTree::Fenwick2DTest* f2dtest = new TwoDimansionalBITFenwickTree::Fenwick2DTest();
    f2dtest->Run();
    delete f2dtest;
      

    BITRangeUpdate::BITRUTest* test = new BITRangeUpdate::BITRUTest();
    test->Run();
    delete test;
    


    SuffixArrayINTRO::SuffixArrayTest* t = new SuffixArrayINTRO::SuffixArrayTest();
    t->Run();
    delete t;

    QuickSort::Run();
    SpanTest::Run();
    RandomInRange::Run();
    OT::Run;
    RomanTest::Run();
    TruckLoadBox::Run();
    return 0;
}
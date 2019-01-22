#pragma once
#include <QObject>


class TestCases : public QObject
{
    Q_OBJECT
private slots:
/*	void initTestCase();
    void cleanupTestCase();
    void testcase1();
    void testcase2();
    void testcase3();
    void testcase4();
    void testcase5();
    void testcase6();
    void testcase7();
    void testcase8();
    void testcase9();
    void testcase10();
    void testcase11();
    void testcase12();
    void testcase13();
    void testcase14();
    void testcase15();
    void testcase16();
    void testcase17();
    void testcase18();
    void testcase19();
    void BenchUnoptimisedCode();
    void BenchOptimisedCode();
    void BenchOptimisedCode2();
    void bench1_stl();
    void bench1_qt();
    void bench_parser();
    void verificator_improove_test();*/
    void parseBigFile();
    void benchPI();
    void compareIssue();
};

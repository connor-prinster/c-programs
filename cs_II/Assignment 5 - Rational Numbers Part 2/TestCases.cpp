
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "TestCases.hpp"
#include "Rational.hpp"


void TestCases::runTestCases()
{
	std::cout << "[=================]" << std::endl;
	std::cout << "[-----------------] Running tests" << std::endl;
	std::cout << "[-----------------]" << std::endl;

	runTest(testCopyConstructorTest, "Copy constructor test case 1");
	runTest(testAssignmentOperatorTest, "Operator= test case 1");
	runTest(testAddCase1, "Add function test case 1");
	runTest(testAddOperatorCase1, "Operator+ test case 1");
	runTest(testAddAssignmentOperatorCase1, "Operator+= test case 1");
	runTest(testSubtractCase1, "Subtract function test case 1");
	runTest(testSubtractOperatorCase1, "Operator- test case 1");
	runTest(testSubtractAssignmentOperatorCase1, "Operator-= test case 1");
	runTest(testDivideCase1, "Divide function test case 1");
	runTest(testDivideOperatorCase1, "Operator/ test case 1");
	runTest(testDivideAssignmentOperatorCase1, "Operator/= test case 1");
	runTest(testMultiplyCase1, "Multiply function test case 1");
	runTest(testMultiplyOperatorCase1, "Operator* test case 1");
	runTest(testMultiplyAssignmentOperatorCase1, "Operator*= test case 1");
	runTest(testPowerCase1, "Power function test case 1");
	runTest(testPowerOperatorCase1, "Operator^ test case 1");
	runTest(testPowerAssignmentOperatorCase1, "Operator^= test case 1");
	runTest(testReciprocalCase1, "Reciprocal function test case 1");
	runTest(testReciprocalOperatorCase1, "Operator~ test case 1");
	runTest(testGetNameCase1, "getName function test case 1");
	runTest(testStreamOperatorCase1, "Stream operator test case 1");
	runTest(testStreamOperatorCase2, "Stream operator test case 2");

	std::cout << "[-----------------]" << std::endl;
	std::cout << "[-----------------] Tests complete" << std::endl;
	std::cout << "[=================]" << std::endl << std::endl;
}

void TestCases::runTest(std::function<bool(void)> testCase, std::string label)
{
	std::cout << "[ Running         ] " << label << std::endl;
	
	if (testCase())
	{
		std::cout << "[            PASS ]";
	}
	else
	{
		std::cout << "[          FAILED ]";
	}

	std::cout << " " << label << std::endl;
}

bool TestCases::testCopyConstructorTest()
{
	Rational ratRes(31, 123, "n/a");
	Rational ratActual(ratRes);

	return EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases::testAssignmentOperatorTest()
{
	Rational ratRes(31, 123, "n/a");
	Rational ratActual(1, 1, "n/a");

	ratActual = ratRes;

	return EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases::testAddCase1()
{
	Rational rat0(3, 2, "n/a");
	Rational rat1(4, 5, "n/a");
	Rational ratRes(23, 10, "n/a");
	Rational ratActual = rat0.add(rat1);

	return EXPECT_EQ(3, rat0.m_numerator) &&
		EXPECT_EQ(2, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases::testAddOperatorCase1()
{
	Rational rat0(1, 2, "n/a");
	Rational rat1(1, 2, "n/a");
	Rational ratRes(1, 1, "n/a");
	Rational ratActual = rat0 + rat1;

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(2, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases::testAddAssignmentOperatorCase1()
{
	Rational rat0(1, 2, "n/a");
	Rational rat1(4, 5, "n/a");
	Rational ratRes(13, 10, "n/a");
	rat0 += rat1;

	return EXPECT_EQ(ratRes.m_numerator, rat0.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, rat0.m_denominator);
}

bool TestCases:: testSubtractCase1()
{
	Rational rat0(1, 2, "n/a");
	Rational rat1(1, 2, "n/a");
	Rational ratRes(0, 2, "n/a");
	Rational ratActual = rat0.subtract(rat1);

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(2, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_GT(ratActual.m_denominator, 0);
}

bool TestCases:: testSubtractOperatorCase1()
{
	Rational rat0(1, 2, "n/a");
	Rational rat1(1, 3, "n/a");
	Rational ratRes(1, 6, "n/a");
	Rational ratActual = rat0 - rat1;

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(2, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases:: testSubtractAssignmentOperatorCase1()
{
	Rational rat0(1, 2, "n/a");
	Rational rat1(3, 1, "n/a");
	Rational ratRes(-5, 2, "n/a");
	rat0 -= rat1;

	return EXPECT_EQ(ratRes.m_numerator, rat0.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, rat0.m_denominator);
}

bool TestCases:: testDivideCase1()
{
	Rational rat0(1, 2, "n/a");
	Rational rat1(1, 3, "n/a");
	Rational ratRes(3, 2, "n/a");
	Rational ratActual = rat0.divide(rat1);

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(2, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases:: testDivideOperatorCase1()
{
	Rational rat0(1, 3, "n/a");
	Rational rat1(3, 45, "n/a");
	Rational ratRes(5, 1, "n/a");
	Rational ratActual = rat0 / rat1;

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(3, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases:: testDivideAssignmentOperatorCase1()
{
	Rational rat0(13, 2, "n/a");
	Rational rat1(3, 45, "n/a");
	Rational ratRes(195, 2, "n/a");
	rat0 /= rat1;

	return EXPECT_EQ(ratRes.m_numerator, rat0.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, rat0.m_denominator);
}

bool TestCases:: testMultiplyCase1()
{
	Rational rat0(1, 2, "n/a");
	Rational rat1(1, 3, "n/a");
	Rational ratRes(1, 6, "n/a");
	Rational ratActual = rat0.multiply(rat1);

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(2, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases:: testMultiplyOperatorCase1()
{
	Rational rat0(1, 3, "n/a");
	Rational rat1(3, 45, "n/a");
	Rational ratRes(1, 45, "n/a");
	Rational ratActual = rat0 * rat1;

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(3, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases:: testMultiplyAssignmentOperatorCase1()
{
	Rational rat0(13, 2, "n/a");
	Rational rat1(3, 45, "n/a");
	Rational ratRes(13, 30, "n/a");
	rat0 *= rat1;

	return EXPECT_EQ(ratRes.m_numerator, rat0.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, rat0.m_denominator);
}

bool TestCases:: testPowerCase1()
{
	Rational rat0(1, 2, "n/a");
	int pow = 4;
	Rational ratRes(1, 16, "n/a");
	Rational ratActual = rat0.power(pow);

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(2, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases:: testPowerOperatorCase1()
{
	Rational rat0(1, 3, "n/a");
	int pow = 2;
	Rational ratRes(1, 9, "n/a");
	Rational ratActual = rat0 ^ pow;

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(3, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases:: testPowerAssignmentOperatorCase1()
{
	Rational rat0(13, 2, "n/");
	int pow = 6;
	Rational ratRes(4826809, 64, "n/a");
	rat0 ^= pow;

	return EXPECT_EQ(ratRes.m_numerator, rat0.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, rat0.m_denominator);
}

bool TestCases:: testReciprocalCase1()
{
	Rational rat0(1, 2, "n/a");
	Rational ratRes(2, 1, "n/a");
	Rational ratActual = rat0.reciprocal();

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(2, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases:: testReciprocalOperatorCase1()
{
	Rational rat0(1, 3, "n/a");
	Rational ratRes(3, 1, "n/a");
	Rational ratActual = ~rat0;

	return EXPECT_EQ(1, rat0.m_numerator) &&
		EXPECT_EQ(3, rat0.m_denominator) &&
		EXPECT_EQ(ratRes.m_numerator, ratActual.m_numerator) &&
		EXPECT_EQ(ratRes.m_denominator, ratActual.m_denominator);
}

bool TestCases:: testGetNameCase1()
{
	std::string name = "3/1";
	Rational ratRes(3, 1, name.c_str());
	return EXPECT_EQ(0, strncmp(name.c_str(), ratRes.getName(), name.length()));
}

bool TestCases:: testStreamOperatorCase1()
{
	std::string expected = "1/3";
	Rational rat0(1, 3, "myVal");
	std::stringstream ss;
	ss << rat0;

	return EXPECT_EQ(expected, ss.str());
}

bool TestCases:: testStreamOperatorCase2()
{
	std::string expected = "3";
	Rational rat0(3, 1, "myVal");
	std::stringstream ss;
	ss << rat0;

	return EXPECT_EQ(expected, ss.str());
}

#include "utils.h"

using namespace std;

void testIPToCIDR();
void testNumSquares();
void testWordDict();
void testToHex();
void testCountPrimeSetBits();
void testHasAlternatingBits();
void testBinaryWatch();
void testRepeatedDNASequences();
void testSubsets();
void testSubsetsWithDup();
void testLargestDivSubset();
void testMaxNumber();
void testShoppingOffers();
void testLongestValidParentheses();
void testMaximalRectangle();
void testNew21Game();
void testNumSquarefulPerms();
void testCutOffTrees();
void testFindLadders();
void testWordSearch();
void testTrie();
void testWordSearchII();
void testWordFilter();
void testRemoveInvalidParentheses();
void testSodukuSolver();
void testNQueens();
void testRecoverBST();
void testFindMedianSortedArrays();
void testIsValidBST();
void testMyCalendarTwo();
void testMyCalendarThree();
void testMyCalendarThreeWithTree();
void testMyCalendarThreeWithTree2();
void testRectangleAreaII();
void testLongestCommonPrefix();
void testNumPermsDISequence();
void testAddOperators();
void testSmallestRange();
void testMinWindow();
void testSubstringConcatenation();
void testPushDominoes();
void testCalcEquation();
void testSurroundedRegions();
void testIsEscapable();

void test(int id){
	using namespace std;
	switch (id)
	{
	case 751:
		cout << "----------Test IP To CIDR-----------" << endl;
		testIPToCIDR();
		break;
	case 279:
		cout << "----------Test Number Of Squares-----------" << endl;
		testNumSquares();
		break;
	case 211:
		cout << "----------Test Word Dictionary-----------" << endl;
		testWordDict();
		break;
	case 405:
		cout << "----------Test Convert A Number To Hexadecimal-----------" << endl;
		testToHex();
		break;
	case 762:
		cout << "----------Test Count of Prime Bit Sets-----------" << endl;
		testCountPrimeSetBits();
		break;
	case 693:
		cout << "----------Test Number With Alternating Bits-----------" << endl;
		testHasAlternatingBits();
		break;
	case 401:
		cout << "----------Test Binary Watch-----------" << endl;
		testBinaryWatch();
		break;
	case 187:
		cout << "----------Test Repeated DNA Sequences-----------" << endl;
		testRepeatedDNASequences();
		break;
	case 78:
		cout << "----------Test Subsets-----------" << endl;
		testSubsets();
		break;
	case 90:
		cout << "----------Test Subsets With Duplicates-----------" << endl;
		testSubsetsWithDup();
		break;
	case 368:
		cout << "----------Test Largest Divisible Subset-----------" << endl;
		testLargestDivSubset();
		break;
	case 321:
		cout << "----------Test Max Number-----------" << endl;
		testMaxNumber();
		break;
	case 638:
		cout << "----------Test Shopping Offers-----------" << endl;
		testShoppingOffers();
		break;
	case 32:
		cout << "----------Test Longest Valid Parentheses-----------" << endl;
		testLongestValidParentheses();
		break;
	case 85:
		cout << "----------Test Maximal Rectangle-----------" << endl;
		testMaximalRectangle();
		break;
	case 837:
		cout << "----------Test New 21 Game-----------" << endl;
		testNew21Game();
		break;
	case 996:
		cout << "----------Test Number of Squareful Permutations-----------" << endl;
		testNumSquarefulPerms();
		break;
	case 675:
		cout << "----------Test Cut Off Trees for Golf Event-----------" << endl;
		testCutOffTrees();
		break;
	case 126:
		cout << "----------Test Finding Ladders-----------" << endl;
		testFindLadders();
		break;
	case 79:
		cout << "----------Test Word Search-----------" << endl;
		testWordSearch();
		break;
	case 208:
		cout << "----------Test Trie Implementation-----------" << endl;
		testTrie();
		break;
	case 212:
		cout << "----------Test Word Search II-----------" << endl;
		testWordSearchII();
		break;
	case 745:
		cout << "----------Test Word Filter-----------" << endl;
		testWordFilter();
		break;
	case 301:
		cout << "----------Test Removing Invalid Parentheses-----------" << endl;
		testRemoveInvalidParentheses();
		break;
	case 37:
		cout << "----------Test Soduku Solver-----------" << endl;
		testSodukuSolver();
		break;
	case 51:
		cout << "----------Test N Queens-----------" << endl;
		testNQueens();
		break;
	case 99:
		cout << "----------Test Recovering BST-----------" << endl;
		testRecoverBST();
		break;
	case 4:
		cout << "----------Test Find Median of Two Sorted Arrays-----------" << endl;
		testFindMedianSortedArrays();
		break;
	case 98:
		cout << "----------Test Validate Binary Search Tree-----------" << endl;
		testIsValidBST();
		break;
	case 731:
		cout << "----------Test My Calendar II-----------" << endl;
		testMyCalendarTwo();
		break;	
	case 732:
		cout << "----------Test My Calendar III-----------" << endl;
		testMyCalendarThreeWithTree2();
		break;	
	case 850:
		cout << "----------Test Rectangle Area II-----------" << endl;
		testRectangleAreaII();
		break;	
	case 14:
		cout << "----------Test Longest Common Prefix-----------" << endl;
		testLongestCommonPrefix();
		break;	
	case 903:
		cout << "----------Test Number of Valid Permutation for DI Sequence-----------" << endl;
		testNumPermsDISequence();
		break;	
	case 282:
		cout << "----------Test Expression Add Operators-----------" << endl;
		testAddOperators();
		break;	
	case 632:
		cout << "----------Test Smallest Range-----------" << endl;
		testSmallestRange();
		break;	
	case 76:
		cout << "----------Test Minimum Window Substring-----------" << endl;
		testMinWindow();
		break;	
	case 30:
		cout << "----------Test Substring Concatenation-----------" << endl;
		testSubstringConcatenation();
		break;	
	case 838:
		cout << "----------Test Push Dominoes-----------" << endl;
		testPushDominoes();
		break;	
	case 399:
		cout << "----------Test Evaluate Divisions-----------" << endl;
		testCalcEquation();
		break;	
	case 130:
		cout << "----------Test Surrounded Regions-----------" << endl;
		testSurroundedRegions();
		break;	
	case 1036:
		cout << "----------Test Escape A Large Maze-----------" << endl;
		testIsEscapable();
		break;	
	default:
		cout << "Problem #" << id << " is not recognized!" << endl;
		break;
	}
}
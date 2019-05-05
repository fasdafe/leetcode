/*
Givena start IP address ip and a numberof ips we need to cover n, return a representation of 
the range as a list (of smallestpossible length) of CIDR blocks.

ACIDR block is a string consisting of an IP, followed by a slash, and then theprefix length. 
For example: "123.45.67.89/20". That prefix length"20" represents the number of common prefix 
bits in the specifiedrange.

Example1:

Input: ip = "255.0.0.7", n = 10

Output:["255.0.0.7/32","255.0.0.8/29","255.0.0.16/32"]

Explanation:

The initial ip address, when converted to binary, looks likethis (spaces added for clarity):

255.0.0.7 -> 11111111 00000000 00000000 00000111

The address "255.0.0.7/32" specifies all addresses with a common prefix of 32 bits to the given address,

ie. just this one address.

The address "255.0.0.8/29" specifies all addresseswith a common prefix of 29 bits to the given address:

255.0.0.8 -> 11111111 00000000 00000000 00001000

Addresses with common prefix of 29 bits are:

11111111 00000000 00000000 00001000

11111111 00000000 00000000 00001001

11111111 00000000 00000000 00001010

11111111 00000000 00000000 00001011

11111111 00000000 00000000 00001100

11111111 00000000 00000000 00001101

11111111 00000000 00000000 00001110

11111111 00000000 00000000 00001111

The address "255.0.0.16/32" specifies all addresseswith a common prefix of 32 bits to the given address,

ie. just 11111111 00000000 00000000 00010000.

In total, the answer specifies the range of 10 ips startingwith the address 255.0.0.7 .

There were other representations, such as:

["255.0.0.7/32","255.0.0.8/30","255.0.0.12/30", "255.0.0.16/32"],

but our answer was the shortest possible.

Also note that a representation beginning with say,"255.0.0.7/30" would be incorrect,

because it includes addresses like 255.0.0.4 = 1111111100000000 00000000 00000100

that are outside the specified range.

Note:

1.      ip will be a valid IPv4 address.

2.      Every implied address ip + x (for x < n) will be a valid IPv4 address.

3.      n will be an integer in the range [1, 1000].
*/


#include <vector>
#include <string>
#include <bitset>

#include "utils.h"

using namespace std;

class Solution {
public:
	long long ipToLong(string ip)
	{
		int start = 0;
		long long result = 0;
		string tmp;
		for (int i = 0; i < 3; i++)
		{
			tmp = ip.substr(start,ip.find_first_of('.', start) -start);
			result = result * 256 + atol(tmp.c_str());
			start = ip.find_first_of('.',start)+1;
		}
		tmp = ip.substr(start,ip.find_first_of(start, ip.size()));
		result = result * 256 + atol(tmp.c_str());
		return result;
	}

	int digit(long long num)
	{
		num += 1; int count = 0;
		while (num > 1)
		{
			num /= 2; count++;
		}
		return count;
	}

	string longToIp(long long num)
	{
		string tmp = "";
		for (int i = 0; i < 3; i++)
		{
			tmp = "." + to_string(num % 256ll)+tmp;
			num /= 256;
		}
		tmp =to_string(num % 256) + tmp;
		return tmp;
	}

	void query(long long l, long long r, long long ll, long long rr, vector<string>&result)
	{
		if (l == ll&&r == rr)
		{
			result.push_back(longToIp(ll) +"/" + to_string(32 - digit(rr - ll))); return;
		}
		long long m = (ll + rr) / 2;
		if (l <= m&&r > m)
		{
			query(l, m, ll, m, result);
			query(m+1, r, m+1,rr, result);
		}
		if (r <= m)
		{
			query(l, r, ll, m, result);
		}
		if (l > m)
		{
			query(l, r, m+1, rr, result);
		}
	}

	vector<string> ipToCIDR(string ip, int range) {
		long long l, ll, r, rr;
		ll = 0;
		rr = 256ll * 256ll * 256ll * 256ll - 1;
		l = ipToLong(ip);
		r = l + range-1;
		vector<string>result;
		query(l, r, ll, rr, result);
		return result;
	}

};


unsigned ipToUnsigned(string ip){
	unsigned ipInt = 0;
	for(int i = 0; i < 4; i++){
		ipInt <<= 8;

		string::size_type sz = ip.find(".");
		string s = ip.substr(0,sz);
		if(sz != string::npos)
			ip = ip.substr(sz+1);

		ipInt += (unsigned)atoi(s.c_str());
	}
	return ipInt;
}

string unsignedToIP(unsigned ipInt){
	string s;

	for(int i = 0; i < 4; i++){
		s = to_string(ipInt%256) + "." + s;
		ipInt >>= 8;
	}

	return s.substr(0, s.length()-1);
}

void ipToCIDR(unsigned ipInt, int range, vector<string>& vec){
	if(range == 0) return;
	unsigned ui = ipInt;
	string s = unsignedToIP(ui);
	int bits = 32;
	unsigned i = 1;
	while(ui%2 == 0 && bits){
		bits--;
		i <<= 1;
		if(i > range){
			vec.push_back(s+"/"+to_string(bits+1));
			ipToCIDR(ipInt+(i>>1), range-(i>>1), vec);
			return;
		}
		ui >>= 1;
	}
	vec.push_back(s+"/"+to_string(bits));
	ipToCIDR(ipInt+i, range-i, vec);
}

vector<string> ipToCIDR(string ip, int range) {
	vector<string> res;
	ipToCIDR(ipToUnsigned(ip), range, res);
	return res;
}

void testIPToCIDR(){

	string ip = "255.0.0.7";
	int range = 10;

	Solution ms;

	vector<string> v = ipToCIDR(ip, range);
	printVector(v);

	v = ipToCIDR("0.0.0.0", 101);
	printVector(v);

}
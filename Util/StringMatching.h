# pragma once
# include "sstream"

namespace ds
{
	template< std::size_t m>
	void compute_prefix(char(&P)[m], int(&prefix)[m])
	{
		prefix[0] = -1;
		int k = -1;
		for (int i = 1; i < m; i++)
		{
			while (k > -1 && P[k + 1] != P[i])
				k = prefix[k];
			if (P[k + 1] == P[i])
				k++;
			prefix[i] = k;
			prefix[i] = k;
		}
	}

	template< std::size_t m, std::size_t n >
	std::string knuth_morris_pratt(char(&T)[n], char(&P)[m])
	{
		std::stringstream ss;
		int prefix[m];
		compute_prefix(P, prefix);
		int k = -1;
		for (int i = 1; i < n; i++)
		{
			while (k > -1 && P[k + 1] != T[i])
				k = prefix[k];
			if (P[k + 1] == T[i])
				k++;
			if (k == m - 2)
			{
				ss << i - k << " ";
				k = prefix[k];
			}
		}
		return (ss.str().empty() ? "None" : ss.str()) + "\n";
	}

}
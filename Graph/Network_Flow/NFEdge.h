#pragma once
namespace ds
{

	class NFEdge
	{
	private:
		const int maxn = 10000;
	public:
		int st, ed, cap, flow;
		NFEdge(int s, int t, int c, int f=0) :st(s), ed(t), cap(c), flow(f) {};
	};
}
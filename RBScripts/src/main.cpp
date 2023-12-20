#define RBS_API __declspec(dllexport)

extern "C"
{
	RBS_API int Test()
	{
		return 48;
	}

	RBS_API int TestPlus(int val)
	{
		return Test() + val;
	}
}

RBS_API int Rest(int val)
{
	return 49;
}
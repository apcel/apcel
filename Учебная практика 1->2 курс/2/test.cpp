#include <iostream>
#include <vector>
#include <iterator>
typedef std::vector<int> row;
int main ()
{
	row sdf;
	std::vector<row> v(10, {0, 1, 2, 3});
	/*for (std::vector<std::vector<int>>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << std::endl;
	}*/
	//copy(v.begin(), v.end(), std::ostream_iterator<std::ostream_iterator<int>>(std::cout, "\n"));
	//int i = &v;
	for (int  i = 0; i != 9; ++i)
	{
		for (int j = 0; j != 4; ++j)
			std::cout << v[i][j] << " " ;
		std::cout << /*v[i].size <<*/ std::endl;
	}

		//copy(v[i].begin, v[i].end, std::ostream_iterator<int>(std::cout, " "));
	//std::cout << v << std::endl;

	//std::cout << &v << std::endl;
	return 0;
}
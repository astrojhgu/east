#include <regex>
#include <string>
#include <iostream>
#include <parser.hpp>

using namespace std;
using namespace east;
int main(int argc,char* argv[])
{
  parser ps;
  if( argc>=2)
    {
      for(int i=1;i<argc;++i)
	{
	  cout<<ps.parse(argv[i])<<endl;
	}
    }
  else
    {
      string line;
      while(cin>>line)
	{
	  cout<<ps.parse(line)<<endl;
	}
    }
}


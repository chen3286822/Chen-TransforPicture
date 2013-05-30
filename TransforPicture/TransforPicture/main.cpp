#include <iostream>
#include <io.h>
#include <fstream>
#include <string>
#include <vector>
#include <direct.h>

using namespace std;


//根据格式文件到源Data目录中寻找特定的图片，然后复制到temp目录中
//并且根据格式文件来进行重命名
//格式文件格式为： 源文件名	目标文件名
//将会从items、dnitems、ptitems 中寻找文件
int main()
{
	string szSrcPath;
	string szTempPath;
	string szFormatFile;

	string szSrcItemPath[3];
	string szTempItemPath[3];

	vector<int> vSrcName;
	vector<int> vTarName;

	cin >> szSrcPath
		>> szTempPath
		>> szFormatFile;

	if (szSrcPath.empty() || szTempPath.empty() || szFormatFile.empty())
	{
		cout << "路径或者格式文件不能为空" << endl;
		return -1;
	}

	szSrcItemPath[0] = szSrcPath + "/items";
	szSrcItemPath[1] = szSrcPath + "/dnitems";
	szSrcItemPath[2] = szSrcPath + "/ptitems";
	szTempItemPath[0] = szTempPath + "/items";
	szTempItemPath[1] = szTempPath + "/dnitems";
	szTempItemPath[2] = szTempPath + "/ptitems";

	//创建temp文件夹内的子文件夹
	for (int m=0;m<3;m++)
	{
		if (access(szTempItemPath[m].c_str(),0) != 0)
		{
			mkdir(szTempItemPath[m].c_str());
		}
	}


	ifstream ifs(szFormatFile);
	while (!ifs.fail())
	{
		int iSrcName = 0;
		int iTarName = 0;
		ifs >> iSrcName >> iTarName;
		vSrcName.push_back(iSrcName);
		vTarName.push_back(iTarName);
	}
	ifs.close();

	if (vSrcName.empty() || vTarName.empty())
	{
		cout << "格式文件内容不能为空" << endl;
		return -2;
	}
	if (vSrcName.size() != vTarName.size())
	{
		cout << "格式文件内容不正确" << endl;
		return -3;
	}


	for (int i=0;i<vSrcName.size();i++)
	{
		if(vSrcName[i] <0 || vTarName[i] <0)
		{
			cout << "格式文件数据错误" << endl;
			return -4;
		}

		int iSrcDir = vSrcName[i]/100;
		int iSrcName = vSrcName[i]%100;
		int iTarDir = vTarName[i]/100;
		int iTarName = vTarName[i]%100;

		for (int j=0;j<3;j++)
		{
			char szSrcFile[255];
			char szTempFile[255];
			char szTempFileDir[255];
			if(iSrcDir < 100)
			{
				sprintf(szSrcFile,"%s/0%d/0%d%d.tex",szSrcItemPath[j].c_str(),iSrcDir,iSrcDir,iSrcName);
			}
			else
			{
				sprintf(szSrcFile,"%s/%d/%d%d.tex",szSrcItemPath[j].c_str(),iSrcDir,iSrcDir,iSrcName);
			}

			if(iTarDir < 100)
			{
				sprintf(szTempFile,"%s/0%d/0%d%d.tex",szTempItemPath[j].c_str(),iTarDir,iTarDir,iTarName);
				sprintf(szTempFileDir,"%s/0%d",szTempItemPath[j].c_str(),iTarDir);
			}
			else
			{
				sprintf(szTempFile,"%s/%d/%d%d.tex",szTempItemPath[j].c_str(),iTarDir,iTarDir,iTarName);
				sprintf(szTempFileDir,"%s/%d",szTempItemPath[j].c_str(),iTarDir);
			}

			ifstream ifsSrc(szSrcFile,ios::binary|ios::in);

			//首先需要创建文件夹
			if (access(szTempFileDir,0) != 0)
			{
				mkdir(szTempFileDir);
			}

			ofstream ofsTemp;
			ofsTemp.open(szTempFile,ios::binary|ios::out);
			if (!ifsSrc.fail() && !ofsTemp.fail())
			{
				ofsTemp << ifsSrc.rdbuf();
			}
			if(ifsSrc.fail())
				cout << iSrcDir << "/" << iSrcDir << vSrcName[i] << "不存在" << endl;
			ofsTemp.close();
			ifsSrc.close();
		}
	}


	return 0;
}
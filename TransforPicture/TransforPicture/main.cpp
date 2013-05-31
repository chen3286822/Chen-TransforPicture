#include <iostream>
#include <io.h>
#include <fstream>
#include <string>
#include <vector>
#include <direct.h>

using namespace std;


//���ݸ�ʽ�ļ���ԴDataĿ¼��Ѱ���ض���ͼƬ��Ȼ���Ƶ�tempĿ¼��
//���Ҹ��ݸ�ʽ�ļ�������������
//��ʽ�ļ���ʽΪ�� Դ�ļ���	Ŀ���ļ���
//�����items��dnitems��ptitems ��Ѱ���ļ�
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
		cout << "·�����߸�ʽ�ļ�����Ϊ��" << endl;
		return -1;
	}

	szSrcItemPath[0] = szSrcPath + "/items";
	szSrcItemPath[1] = szSrcPath + "/dnitems";
	szSrcItemPath[2] = szSrcPath + "/ptitems";
	szTempItemPath[0] = szTempPath + "/items";
	szTempItemPath[1] = szTempPath + "/dnitems";
	szTempItemPath[2] = szTempPath + "/ptitems";

	//����temp�ļ����ڵ����ļ���
	for (int m=0;m<3;m++)
	{
		if (access(szTempItemPath[m].c_str(),0) != 0)
		{
			mkdir(szTempItemPath[m].c_str());
		}
	}


	ifstream ifs(szFormatFile);
	while (!ifs.eof())
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
		cout << "��ʽ�ļ����ݲ���Ϊ��" << endl;
		return -2;
	}
	if (vSrcName.size() != vTarName.size())
	{
		cout << "��ʽ�ļ����ݲ���ȷ" << endl;
		return -3;
	}


	for (int i=0;i<vSrcName.size();i++)
	{
		if(vSrcName[i] <0 || vTarName[i] <0)
		{
			cout << "��ʽ�ļ����ݴ���" << endl;
			return -4;
		}

		int iSrcDir = vSrcName[i]/100;
		int iSrcName = vSrcName[i]%100;
		int iTarDir = vTarName[i]/100;
		int iTarName = vTarName[i]%100;

		char szRealSrcDir[10];
		char szRealSrcName[20];
		char szRealTarDir[10];
		char szRealTarName[20];
		if(iSrcDir < 10)
			sprintf(szRealSrcDir,"00%d",iSrcDir);
		else if(iSrcDir < 100)
			sprintf(szRealSrcDir,"0%d",iSrcDir);
		else
			sprintf(szRealSrcDir,"%d",iSrcDir);
		if(iSrcName < 10)
			sprintf(szRealSrcName,"0%d.tex",iSrcName);
		else
			sprintf(szRealSrcName,"%d.tex",iSrcName);

		if(iTarDir < 10)
			sprintf(szRealTarDir,"00%d",iTarDir);
		else if(iTarDir < 100)
			sprintf(szRealTarDir,"0%d",iTarDir);
		else
			sprintf(szRealTarDir,"%d",iTarDir);
		if(iTarName < 10)
			sprintf(szRealTarName,"0%d.tex",iTarName);
		else
			sprintf(szRealTarName,"%d.tex",iTarName);

		for (int j=0;j<3;j++)
		{
			char szSrcFile[255];
			char szTempFile[255];
			char szTempFileDir[255];
			sprintf(szSrcFile,"%s/%s/%s%s",szSrcItemPath[j].c_str(),szRealSrcDir,szRealSrcDir,szRealSrcName);
			sprintf(szTempFile,"%s/%s/%s%s",szTempItemPath[j].c_str(),szRealTarDir,szRealTarDir,szRealTarName);
			sprintf(szTempFileDir,"%s/%s",szTempItemPath[j].c_str(),szRealTarDir);

			ifstream ifsSrc(szSrcFile,ios::binary|ios::in);
			if(ifsSrc.fail())
			{
				cout << szSrcFile  << "������" << endl;
				ifsSrc.close();
				continue;
			}

			//������Ҫ�����ļ���
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

			ofsTemp.close();
			ifsSrc.close();
		}
	}

	system("pause");
	return 0;
}
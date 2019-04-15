#include "DataManager.h"
#include "json/document.h"
#include "json/rapidjson.h"

using namespace rapidjson;

//��̬����
static DataManager * dataManager = nullptr;

DataManager * DataManager::getInstance()
{
	if (dataManager == nullptr)
	{
		dataManager = new DataManager();
	}

	return dataManager;
}

void DataManager::initWithJsonFile(const char * filename)
{
	//��json�����ȡ��Ϣ
	tollgateData = FileUtils::getInstance()->getStringFromFile(filename);
	log("�ؿ����ݣ�%s", tollgateData.c_str());
}

std::vector<std::string> DataManager::getLevelDataArrayByIndex(int index)
{
	//����һ������
	Document doc;
	//ִ��parse����
	doc.Parse<kParseDefaultFlags>(tollgateData.c_str());
	_levelDataArray.clear();
	//ȡ���������͵�ֵ
	rapidjson::Value & array = doc["Tollgate"];
	if (array.IsArray())
	{
		int i = index;		//�ؿ����
		unsigned int j = 0;
		for (j = 0; j < array[i]["RoleData"].Size(); j++)
		{
			rapidjson::Value & str = array[i]["RoleData"][j];
			//��ӵ��ؿ���������
			_levelDataArray.push_back(str.GetString());
		}
	}
	return  _levelDataArray;
}

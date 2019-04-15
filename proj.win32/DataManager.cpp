#include "DataManager.h"
#include "json/document.h"
#include "json/rapidjson.h"

using namespace rapidjson;

//静态变量
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
	//从json里面读取信息
	tollgateData = FileUtils::getInstance()->getStringFromFile(filename);
	log("关卡数据：%s", tollgateData.c_str());
}

std::vector<std::string> DataManager::getLevelDataArrayByIndex(int index)
{
	//创建一个对象
	Document doc;
	//执行parse方法
	doc.Parse<kParseDefaultFlags>(tollgateData.c_str());
	_levelDataArray.clear();
	//取出数组类型的值
	rapidjson::Value & array = doc["Tollgate"];
	if (array.IsArray())
	{
		int i = index;		//关卡编号
		unsigned int j = 0;
		for (j = 0; j < array[i]["RoleData"].Size(); j++)
		{
			rapidjson::Value & str = array[i]["RoleData"][j];
			//添加到关卡容器里面
			_levelDataArray.push_back(str.GetString());
		}
	}
	return  _levelDataArray;
}

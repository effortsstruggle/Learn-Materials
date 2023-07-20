#include "GeneratorFactory.h"

#include <QDebug>
#include <qvariant.h>
#include <qfile.h>
#include <qcoreapplication.h>
#include <qdom.h>
#include <QString>
#include <glog/logging.h>

//通过工厂 生成  专有事件生成器
IGenerator* GeneratorFactory::create_generator(QObject* object)
{
    if(config_map().isEmpty())
    {
        read_config();
    }

    QString key = object->metaObject()->className();
	if (config_map().contains(key) && class_map().contains(config_map().value(key))) {
		//专有事件生成器
		IGenerator* generator = qobject_cast<IGenerator*>(class_map().value(config_map().value(key)).newInstance());
		
		//	专有事件生成器中，设置需生成的具体事件
		generator->set_resource(object);

		return generator;
    }
	return nullptr;
}

void GeneratorFactory::read_config()
{
	QString path = QCoreApplication::applicationDirPath() + "/config_file/xml/EventGenerator.xml";
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
        LOG(INFO) << "GeneratorFactory::read_config() -- EventGenerator.xml文件没有找到";
		throw QString("no config file of generator");
	}

	//解析xml文件
	QDomDocument doc;
	doc.setContent(file.readAll());
	file.close();
	QDomElement root = doc.firstChildElement();
	QDomElement generators = root.elementsByTagName("Generators").at(0).toElement();
	QDomNodeList generator_list = generators.elementsByTagName("Generator");
	
	for (int index = 0; index < generator_list.size(); index++) {
		auto node = generator_list.at(index);
		if (node.isElement()) {
			auto generator = node.toElement();
			QString input = generator.attribute("input");
			QString generator_class = generator.text();
			//建立input 与 所需类名建立映射 如（ArrivedTakeoffJW(到达起飞JW对象) --- TakeoffGenerator（起飞事件生成器））
			config_map().insert(input, generator_class);
		}
	}
}


#ifndef GENERATORFACTORY_H_
#define GENERATORFACTORY_H_
#include <qmap.h>
#include "../generator/igenerator.h"
#include "../common/event_generator_global.h"
#include <QString>
class EVENT_GENERATOR_EXPORT GeneratorFactory
{
public:
	template<typename T>
	static bool regist_generator() {
		class_map().insert(T::staticMetaObject.className(), T::staticMetaObject);
		return true;
	};

	static IGenerator* create_generator(QObject* object);

	static void read_config();

private:
	static QMap<QString, QMetaObject>& class_map() {
		static QMap<QString, QMetaObject> name_class_map;
		return name_class_map;
	};

	/// <summary>
	/// 创建对象和工厂之间的对应关系
	/// </summary>
	/// <returns></returns>
	static QMap<QString, QString>& config_map() {
		static QMap<QString, QString> map;
		return map;
	}
};

#endif

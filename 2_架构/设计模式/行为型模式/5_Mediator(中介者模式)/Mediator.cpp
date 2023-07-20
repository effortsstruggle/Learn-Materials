
class Colleague;
class ConcreteColleague1;
class ConcreteColleague2;
 
//Mediator类 抽象中介者
class Mediator{
 
public:
	//用于各对象通信的接口
	virtual void send(const string &message, Colleague *colleague) = 0;
	virtual ~Mediator(){}
 
	Mediator(){}
	Mediator(Mediator &m){}
	Mediator &operator = (Mediator &m){return Mediator()}
};

// ConcreteMediator类 具体中介者类
class ConcreteMediator: public Mediator{
 
public:
	void send(const string &message, Colleague *colleague)
	{
		if(colleague == this->m_colleague1){
			this->m_colleague2->notify(message);
		}
		else if(colleague == this->m_colleague2){
			this->m_colleague1->notify(message);
		}
		else{
			assert(!"雅喵蝶");
		}
	}

	//设置Colleague1对象
	void setConcreteColleague1(Colleague *colleague)
	{
		this->m_colleague1 = colleague;
	}
	//设置Colleague2对象
	void setConcreteColleague2(Colleague *colleague)
	{
		this->m_colleague2 = colleague;
	}
	
	
	~ConcreteMediator();
 
private:
	//可以使用容器，用键值对形式构成容器对象；
	Colleague *m_colleague1; 
	Colleague *m_colleague2;
};


 
// Colleague类 抽象同事类
class Colleague{
 
public:
	Colleague(Mediator *mediator){this->m_mediator = mediator}
	~Colleague();
 
protected:
	Mediator *m_mediator;
};
 

//ConcreteColleague1和ConcreteColleague2等各种同事对象
class ConcreteColleague1: public Colleague{
 
public:
	ConcreteColleague1(Mediator *mediator):Colleague(mediator)
	{
		
	}
	
	~ConcreteColleague1()
	{
		cout << "ConcreteColleague1::~ConcreteColleague1()" << endl;
	}
	
	void send(const string &message )
	{
		this->m_mediator->send(message , this);
	}
	
	void notify(const string &message)
	{
		cout << "同事1得到信息: " << message << endl;
	}
 
};
 
class ConcreteColleague2: public Colleague{
 
public:
	ConcreteColleague2(Mediator *mediator):Colleague(mediator)
	{
		
	}
	~ConcreteColleague2()
	{
		cout << "ConcreteColleague2::~ConcreteColleague2()" << endl;
	}
	
	void send(const string &message)
	{
		this->m_mediator->send(message, this);
	}
	
	void notify(const string &message)
	{
		cout << "同事2得到信息: " << message << endl;
	}
 
};




int main(int *argc, int *argv[]){
 
	Mediator *m = new ConcreteMediator;
	
	ConcreteColleague1 *c1 = new ConcreteColleague1(m);
	ConcreteColleague2 *c2 = new ConcreteColleague2(m);
 
	m->setConcreteColleague1(c1);
	m->setConcreteColleague2(c2);
 
	c1->send("吃饭了吗？");
	c2->send("你猜！");
 
 
	delete m;
	delete c1;
	delete c2;
 
	return 0;
}

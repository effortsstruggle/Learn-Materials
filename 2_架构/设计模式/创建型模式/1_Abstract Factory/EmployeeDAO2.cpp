
//数据库访问有关的基类

//IDBConnection
class IDBConnection{
    
};
//IDBConnection工厂
class IDBConnectionFactory{
public:
    virtual IDBConnection* CreateDBConnection()=0;
};

//IDBCommand  
class IDBCommand{
    
};
//IDBCommand工厂
class IDBCommandFactory{
public:
    virtual IDBCommand* CreateDBCommand()=0;
};

//IDataReader
class IDataReader{
    
};
//IDataReader工厂
class IDataReaderFactory{
public:
    virtual IDataReader* CreateDataReader()=0;
};


//支持SQL Server
class SqlConnection: public IDBConnection{
    
};
class SqlConnectionFactory:public IDBConnectionFactory{
    
};


class SqlCommand: public IDBCommand{
    
};
class SqlCommandFactory:public IDBCommandFactory{
    
};


class SqlDataReader: public IDataReader{
    
};
class SqlDataReaderFactory:public IDataReaderFactory{
    
};

//支持Oracle
class OracleConnection: public IDBConnection{
    
};
class OracleConnectionFactory:public IDBConnectionFactory{
    
};

class OracleCommand: public IDBCommand{
    
};
class OracleCommandFactory:public IDBCommandFactory{
    
};

class OracleDataReader: public IDataReader{
    
};
class OracleDataReaderFactory:public IDataReaderFactory{
    
};



class EmployeeDAO{
	
    IDBConnectionFactory* dbConnectionFactory;
    IDBCommandFactory* dbCommandFactory;
    IDataReaderFactory* dataReaderFactory;
    
    
public:
    vector<EmployeeDO> GetEmployees(){
        IDBConnection* connection =
            dbConnectionFactory->CreateDBConnection();
        connection->ConnectionString("...");

        IDBCommand* command =
            dbCommandFactory->CreateDBCommand();
        command->CommandText("...");
        command->SetConnection(connection); //关联性

        IDBDataReader* reader = command->ExecuteReader(); //关联性
        while (reader->Read()){

        }

    }
};

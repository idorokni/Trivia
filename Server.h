#pragma once
#include "Communicator.h"
#include "SqliteDataBase.h"
#include <thread>

class Server {
public:
	void run();

private:
	Communicator m_communicator;
};
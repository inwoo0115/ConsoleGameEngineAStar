#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{
}

Level::~Level()
{
	// 메모리 해제.
	for (Actor* actor : actors)
	{
		delete actor;
	}
}

void Level::AddActor(Actor* newActor)
{
	//actors.PushBack(newActor);
	addRequestedActors.emplace_back(newActor);
}

void Level::ProcessAddedAndDestroyedActor()
{
	// 액터 순회 후 삭제 요청된 액터를 처리.
	for (int ix = 0; ix < actors.size();)
	{
		if (actors[ix]->isExpired)
		{
			delete actors[ix];
			actors[ix] = nullptr;
			actors.erase(actors.begin() + ix);
			continue;
		}

		++ix;
	}

	// 추가 요청된 액터 처리.
	if (addRequestedActors.size() > 0)
	{
		for (Actor* newActor : addRequestedActors)
		{
			actors.emplace_back(newActor);
		}
		
		addRequestedActors.clear();
	}
}

void Level::Update(float deltaTime)
{
	// 레벨에 포함된 액터를 순회하면서 Update 함수 호출.
	for (Actor* actor : actors)
	{
		// 액터가 비활성화 상태이거나, 삭제 요청된 경우 건너뛰기.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	// 레벨에 포함된 액터를 순회하면서 Draw 함수 호출.
	for (Actor* actor : actors)
	{
		// 액터가 비활성화 상태이거나, 삭제 요청된 경우 건너뛰기.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Draw();
	}
}

std::vector<std::vector<int>> Level::OpenMapFile(const char* map)
{
	FILE* file = nullptr;

	int error = fopen_s(&file, map, "rb");
	if (error != 0) {
		std::cerr << "Error: Unable to open file. Error code: " << error << std::endl;
		return {};
	}

	//파일 읽기 + 끝위치로 이동
	fseek(file, 0, SEEK_END);
	//이동한 위치 fp 가져오기
	size_t readSize = ftell(file);
	//fp 원위치
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	//파일 읽어서 버퍼에 담기
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름\n";
		return {};
	}

	buffer[readSize] = '\0';

	std::vector<std::vector<int>> grid;

	int i = 0;
	while (i < (int)bytesRead)
	{
		std::vector<int> row;
		while (buffer[i] != '\n' && buffer[i] != '\0')
		{
			row.push_back(buffer[i] - 48);
			++i;
		}
		grid.push_back(row);
		++i;
	}
	fclose(file);
	delete[] buffer;
	return grid;
}

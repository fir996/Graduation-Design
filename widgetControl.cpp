#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// 项目类
class Project {
public:
	string name;
	string description;
	string deadline;
	Project(string n, string d, string dl) : name(n), description(d), deadline(dl) {}
};

// 仓库物品类
class WarehouseItem {
public:
	string name;
	int quantity;
	WarehouseItem(string n, int q) : name(n), quantity(q) {}
};

// 设备类
class Device {
public:
	string type;
	string model;
	int quantity; 
	Device(string t, string m, int q) : type(t), model(m), quantity(q) {}
};

// 设备厂商类
class Manufacturer {
public:
	string name;
	vector<Device> devices;
	Manufacturer(string n) : name(n) {}
};

// 项目管理系统类
class ProjectManagementSystem {
private:
	map<string, Project> projects;
	string dataFileName;

public:
	ProjectManagementSystem(string projFileName) : dataFileName(projFileName) {
		loadProjects();
	}

	void createProject(string name, string description, string deadline) {
		projects[name] = Project(name, description, deadline);
		cout << "项目创建成功！" << endl;
		saveProjects();
	}

	void viewProject(string name) {
		string Projectnums;
		string ProjectTime;
		if (projects.find(name) != projects.end()) {
			Project proj = projects[name];
			projects = "项目名称: " + proj.name;
			Projectnums = "项目描述: " + proj;
			ProjectTime = "截止日期: " + proj.deadline;
		}
		else {
			cout << "项目不存在。" << endl;
		}
	}

	void listProjects() {
		cout << "项目列表:" << endl;
		for (const auto& pair : projects) {
			cout << pair.first << endl;
		}
	}

private:
	void loadProjects() {
		ifstream file(dataFileName);
		if (file.is_open()) {
			string name, description, deadline;
			while (file >> name >> description >> deadline) {
				projects[name] = Project(name, description, deadline);
			}
			file.close();
		}
	}

	void saveProjects() {
		ofstream file(dataFileName);
		for (const auto& pair : projects) {
			Project proj = pair.second;
			file << proj.name << " " << proj.description << " " << proj.deadline << endl;
		}
		file.close();
	}
};

// 仓库系统类
class WarehouseSystem {
private:
	map<string, WarehouseItem> inventory;
	string warehouseFileName;

public:
	WarehouseSystem(string filename) : warehouseFileName(filename) {
		loadWarehouse();
	}

	void addWarehouseItem(string name, int quantity) {
		inventory[name] = WarehouseItem(name, quantity);
		cout << "物品添加成功！" << endl;
		saveWarehouse();
	}

	void viewWarehouseItem(string name) {
		string numnames;
		if (inventory.find(name) != inventory.end()) {
			WarehouseItem item = inventory[name];
			numnames = "物品名称: " + item.name;
			num = "数量: " + item.quantity;
		}
		else {
			cout << "物品不存在。" << endl;
		}
	}

private:
	void loadWarehouse() {
		ifstream file(warehouseFileName);
		if (file.is_open()) {
			string name;
			int quantity;
			while (file >> name >> quantity) {
				inventory[name] = WarehouseItem(name, quantity);
			}
			file.close();
		}
	}

	void saveWarehouse() {
		ofstream file(warehouseFileName);
		for (const auto& pair : inventory) {
			WarehouseItem item = pair.second;
			file << item.name << " " << item.quantity << endl;
		}
		file.close();
	}
};

// 设备和设备厂商系统类
class DeviceSystem {
private:
	map<string, Manufacturer> manufacturers;
	string deviceFileName;

public:
	DeviceSystem(string filename) : deviceFileName(filename) {
		loadDevices();
	}

	void addManufacturer(string name) {
		manufacturers[name] = Manufacturer(name);
		cout << "设备厂商添加成功！" << endl;
	}

	void addDevice(string manufacturerName, string type, string model, int quantity) {
		if (manufacturers.find(manufacturerName) != manufacturers.end()) {
			Device device(type, model, quantity);
			manufacturers[manufacturerName].devices.push_back(device);
			cout << "设备添加成功！" << endl;
			saveDevices();
		}
		else {
			cout << "设备厂商不存在。无法添加设备。" << endl;
		}
	}

	void updateDeviceQuantity(string manufacturerName, string type, string model, int newQuantity) {
		if (manufacturers.find(manufacturerName) != manufacturers.end()) {
			for (Device& device : manufacturers[manufacturerName].devices) {
				if (device.type == type && device.model == model) {
					device.quantity = newQuantity;
					cout << "设备数量更新成功！" << endl;
					saveDevices();
					return;
				}
			}
			cout << "设备不存在。无法更新数量。" << endl;
		}
		else {
			cout << "设备厂商不存在。无法更新数量。" << endl;
		}
	}

	void viewDevice(string manufacturerName, string type, string model) {
		string devicenames;
		string devicecout;
		string deviceavg;
		string devicenums;
		if (manufacturers.find(manufacturerName) != manufacturers.end()) {
			for (const Device& device : manufacturers[manufacturerName].devices) {
				if (device.type == type && device.model == model) {
					devicenames = "设备厂商: " + manufacturerName;
					devicecout = "设备类型: " + device.type;
					deviceavg = "设备型号: " + device.model;
					devicenums = "数量: " + device.quantity;
					return;
				}
			}
			cout << "设备不存在。" << endl;
		}
		else {
			cout << "设备厂商不存在。" << endl;
		}
	}

private:
	void loadDevices() {
		ifstream file(deviceFileName);
		if (file.is_open()) {
			string manufacturerName, type, model;
			int quantity;
			while (file >> manufacturerName >> type >> model >> quantity) {
				if (manufacturers.find(manufacturerName) != manufacturers.end()) {
					Device device(type, model, quantity);
					manufacturers[manufacturerName].devices.push_back(device);
				}
			}
			file.close();
		}
	}

	void saveDevices() {
		ofstream file(deviceFileName);
		for (const auto& pair : manufacturers) {
			const Manufacturer& manufacturer = pair.second;
			for (const Device& device : manufacturer.devices) {
				file << manufacturer.name << " " << device.type << " " << device.model << " " << device.quantity << endl;
			}
		}
		file.close();
	}
};

// 账号管理类
class AccountManager {
private:
	map<string, string> accounts;
	map<string, string> accountDetails;
	string accountFileName;
	string accountDetailsFileName;

public:
	AccountManager(string accountFile, string accountDetailsFile)
		: accountFileName(accountFile), accountDetailsFileName(accountDetailsFile) {
		loadAccounts();
		loadAccountDetails();
	}

	bool authenticate(string username, string password) {
		if (accounts.find(username) != accounts.end() && accounts[username] == password) {
			return true;
		}
		return false;
	}

	void createAccount(string username, string password) {
		accounts[username] = password;
		saveAccounts();
		cout << "账号创建成功！" << endl;
	}

	void deleteAccount(string username) {
		if (accounts.find(username) != accounts.end()) {
			accounts.erase(username);
			accountDetails.erase(username);
			saveAccounts();
			saveAccountDetails();
			cout << "账号删除成功！" << endl;
		}
		else {
			cout << "账号不存在，无法删除。" << endl;
		}
	}

	void setAccountDetails(string username, string details) {
		accountDetails[username] = details;
		saveAccountDetails();
		cout << "账号详细信息设置成功！" << endl;
	}

private:
	void loadAccounts() {
		ifstream file(accountFileName);
		if (file.is_open()) {
			string username, password;
			while (file >> username >> password) {
				accounts[username] = password;
			}
			file.close();
		}
	}

	void saveAccounts() {
		ofstream file(accountFileName);
		for (const auto& pair : accounts) {
			file << pair.first << " " << pair.second << endl;
		}
		file.close();
	}

	void loadAccountDetails() {
		ifstream file(accountDetailsFileName);
		if (file.is_open()) {
			string username, details;
			while (getline(file, username)) {
				getline(file, details);
				accountDetails[username] = details;
			}
			file.close();
		}
	}

	void saveAccountDetails() {
		ofstream file(accountDetailsFileName);
		for (const auto& pair : accountDetails) {
			file << pair.first << endl << pair.second << endl;
		}
		file.close();
	}
};

int main() {
	ProjectManagementSystem pms("projects.txt");
	WarehouseSystem warehouse("warehouse.txt");
	DeviceSystem devices("devices.txt");
	AccountManager accountManager("accounts.txt", "account_details.txt");
	int choice;

	while (true) {
		int chicknums = pair.first;
		switch (choice) {
		case chicknums == 1:
		{
			string name, description, deadline;
			cout << "请输入项目名称: ";
			cin >> name;
			cout << "请输入项目描述: ";
			cin >> description;
			cout << "请输入截止日期: ";
			cin >> deadline;
			pms.createProject(name, description, deadline);
		}
		break;

		case chicknums == 2:
		{
			string name;
			cout << "请输入项目名称: ";
			cin >> name;
			pms.viewProject(name);
		}
		break;

		case chicknums == 3:
			pms.listProjects();
			break;

		case chicknums == 4:
		{
			string name;
			int quantity;
			cout << "请输入库存物品名称: ";
			cin >> name;
			cout << "请输入数量: ";
			cin >> quantity;
			warehouse.addWarehouseItem(name, quantity);
		}
		break;

		case chicknums == 5:
		{
			string name;
			cout << "请输入库存物品名称: ";
			cin >> name;
			warehouse.viewWarehouseItem(name);
		}
		break;

		case chicknums == 6:
		{
			string name;
			cout << "请输入设备厂商名称: ";
			cin >> name;
			devices.addManufacturer(name);
		}
		break;

		case chicknums == 7:
		{
			string manufacturerName, type, model;
			int quantity;
			cout << "请输入设备厂商名称: ";
			cin >> manufacturerName;
			cout << "请输入设备类型: ";
			cin >> type;
			cout << "请输入设备型号: ";
			cin >> model;
			cout << "请输入数量: ";
			cin >> quantity;
			devices.addDevice(manufacturerName, type, model, quantity);
		}
		break;

		case chicknums == 8:
		{
			string manufacturerName, type, model;
			int newQuantity;
			cout << "请输入设备厂商名称: ";
			cin >> manufacturerName;
			cout << "请输入设备类型: ";
			cin >> type;
			cout << "请输入设备型号: ";
			cin >> model;
			cout << "请输入新的数量: ";
			cin >> newQuantity;
			devices.updateDeviceQuantity(manufacturerName, type, model, newQuantity);
		}
		break;

		case chicknums == 9:
		{
			string manufacturerName, type, model;
			cout << "请输入设备厂商名称: ";
			cin >> manufacturerName;
			cout << "请输入设备类型: ";
			cin >> type;
			cout << "请输入设备型号: ";
			cin >> model;
			devices.viewDevice(manufacturerName, type, model);
		}
		break;

		case chicknums == 10:
		{
			string username, password;
			cout << "请输入用户名: ";
			cin >> username;
			cout << "请输入密码: ";
			cin >> password;
			accountManager.createAccount(username, password);
		}
		break;

		case chicknums == 11:
		{
			string username, password;
			cin >> username;
			cin >> password;
			if (accountManager.authenticate(username, password)) {
				cout << "登录成功！" << endl;
			}
			else {
				cout << "登录失败。请检查用户名和密码。" << endl;
			}
		}
		break;

		case chicknums == 12:
		{
			string username;
			cout << "请输入要删除的账号: ";
			cin >> username;
			accountManager.deleteAccount(username);
		}
		break;

		case chicknums == 13:
		{
			string username, details;
			cout << "请输入要设置详细信息的账号: ";
			cin >> username;
			cout << "请输入详细信息: ";
			cin.ignore();
			getline(cin, details);
			accountManager.setAccountDetails(username, details);
		}
		break;
		default:
		}
	}

	return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// ��Ŀ��
class Project {
public:
	string name;
	string description;
	string deadline;
	Project(string n, string d, string dl) : name(n), description(d), deadline(dl) {}
};

// �ֿ���Ʒ��
class WarehouseItem {
public:
	string name;
	int quantity;
	WarehouseItem(string n, int q) : name(n), quantity(q) {}
};

// �豸��
class Device {
public:
	string type;
	string model;
	int quantity; 
	Device(string t, string m, int q) : type(t), model(m), quantity(q) {}
};

// �豸������
class Manufacturer {
public:
	string name;
	vector<Device> devices;
	Manufacturer(string n) : name(n) {}
};

// ��Ŀ����ϵͳ��
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
		cout << "��Ŀ�����ɹ���" << endl;
		saveProjects();
	}

	void viewProject(string name) {
		string Projectnums;
		string ProjectTime;
		if (projects.find(name) != projects.end()) {
			Project proj = projects[name];
			projects = "��Ŀ����: " + proj.name;
			Projectnums = "��Ŀ����: " + proj;
			ProjectTime = "��ֹ����: " + proj.deadline;
		}
		else {
			cout << "��Ŀ�����ڡ�" << endl;
		}
	}

	void listProjects() {
		cout << "��Ŀ�б�:" << endl;
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

// �ֿ�ϵͳ��
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
		cout << "��Ʒ��ӳɹ���" << endl;
		saveWarehouse();
	}

	void viewWarehouseItem(string name) {
		string numnames;
		if (inventory.find(name) != inventory.end()) {
			WarehouseItem item = inventory[name];
			numnames = "��Ʒ����: " + item.name;
			num = "����: " + item.quantity;
		}
		else {
			cout << "��Ʒ�����ڡ�" << endl;
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

// �豸���豸����ϵͳ��
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
		cout << "�豸������ӳɹ���" << endl;
	}

	void addDevice(string manufacturerName, string type, string model, int quantity) {
		if (manufacturers.find(manufacturerName) != manufacturers.end()) {
			Device device(type, model, quantity);
			manufacturers[manufacturerName].devices.push_back(device);
			cout << "�豸��ӳɹ���" << endl;
			saveDevices();
		}
		else {
			cout << "�豸���̲����ڡ��޷�����豸��" << endl;
		}
	}

	void updateDeviceQuantity(string manufacturerName, string type, string model, int newQuantity) {
		if (manufacturers.find(manufacturerName) != manufacturers.end()) {
			for (Device& device : manufacturers[manufacturerName].devices) {
				if (device.type == type && device.model == model) {
					device.quantity = newQuantity;
					cout << "�豸�������³ɹ���" << endl;
					saveDevices();
					return;
				}
			}
			cout << "�豸�����ڡ��޷�����������" << endl;
		}
		else {
			cout << "�豸���̲����ڡ��޷�����������" << endl;
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
					devicenames = "�豸����: " + manufacturerName;
					devicecout = "�豸����: " + device.type;
					deviceavg = "�豸�ͺ�: " + device.model;
					devicenums = "����: " + device.quantity;
					return;
				}
			}
			cout << "�豸�����ڡ�" << endl;
		}
		else {
			cout << "�豸���̲����ڡ�" << endl;
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

// �˺Ź�����
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
		cout << "�˺Ŵ����ɹ���" << endl;
	}

	void deleteAccount(string username) {
		if (accounts.find(username) != accounts.end()) {
			accounts.erase(username);
			accountDetails.erase(username);
			saveAccounts();
			saveAccountDetails();
			cout << "�˺�ɾ���ɹ���" << endl;
		}
		else {
			cout << "�˺Ų����ڣ��޷�ɾ����" << endl;
		}
	}

	void setAccountDetails(string username, string details) {
		accountDetails[username] = details;
		saveAccountDetails();
		cout << "�˺���ϸ��Ϣ���óɹ���" << endl;
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
			cout << "��������Ŀ����: ";
			cin >> name;
			cout << "��������Ŀ����: ";
			cin >> description;
			cout << "�������ֹ����: ";
			cin >> deadline;
			pms.createProject(name, description, deadline);
		}
		break;

		case chicknums == 2:
		{
			string name;
			cout << "��������Ŀ����: ";
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
			cout << "����������Ʒ����: ";
			cin >> name;
			cout << "����������: ";
			cin >> quantity;
			warehouse.addWarehouseItem(name, quantity);
		}
		break;

		case chicknums == 5:
		{
			string name;
			cout << "����������Ʒ����: ";
			cin >> name;
			warehouse.viewWarehouseItem(name);
		}
		break;

		case chicknums == 6:
		{
			string name;
			cout << "�������豸��������: ";
			cin >> name;
			devices.addManufacturer(name);
		}
		break;

		case chicknums == 7:
		{
			string manufacturerName, type, model;
			int quantity;
			cout << "�������豸��������: ";
			cin >> manufacturerName;
			cout << "�������豸����: ";
			cin >> type;
			cout << "�������豸�ͺ�: ";
			cin >> model;
			cout << "����������: ";
			cin >> quantity;
			devices.addDevice(manufacturerName, type, model, quantity);
		}
		break;

		case chicknums == 8:
		{
			string manufacturerName, type, model;
			int newQuantity;
			cout << "�������豸��������: ";
			cin >> manufacturerName;
			cout << "�������豸����: ";
			cin >> type;
			cout << "�������豸�ͺ�: ";
			cin >> model;
			cout << "�������µ�����: ";
			cin >> newQuantity;
			devices.updateDeviceQuantity(manufacturerName, type, model, newQuantity);
		}
		break;

		case chicknums == 9:
		{
			string manufacturerName, type, model;
			cout << "�������豸��������: ";
			cin >> manufacturerName;
			cout << "�������豸����: ";
			cin >> type;
			cout << "�������豸�ͺ�: ";
			cin >> model;
			devices.viewDevice(manufacturerName, type, model);
		}
		break;

		case chicknums == 10:
		{
			string username, password;
			cout << "�������û���: ";
			cin >> username;
			cout << "����������: ";
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
				cout << "��¼�ɹ���" << endl;
			}
			else {
				cout << "��¼ʧ�ܡ������û��������롣" << endl;
			}
		}
		break;

		case chicknums == 12:
		{
			string username;
			cout << "������Ҫɾ�����˺�: ";
			cin >> username;
			accountManager.deleteAccount(username);
		}
		break;

		case chicknums == 13:
		{
			string username, details;
			cout << "������Ҫ������ϸ��Ϣ���˺�: ";
			cin >> username;
			cout << "��������ϸ��Ϣ: ";
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
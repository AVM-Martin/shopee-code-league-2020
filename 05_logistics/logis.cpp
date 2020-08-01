#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

string city[4] = {"metro manila", "luzon", "visayas", "mindanao"};

int sla[4][4] = {{3,5,7,7},{5,5,7,7},{7,7,7,7},{7,7,7,7}};

struct datim{
	int type, year, month, day, hour, minute, second;
};

struct data{
	datim pick, send1, send2;
	ll orderId;
	int buyer, seller;
	int arr1, arr2;
	bool isLate;
};

ll get_num(string x, int &id, char sep=','){
	ll ret = 0ll;
	while(id < x.size()){
		if(x[id] == sep) break;
		if(x[id] == '.'){
			while(x[id] != sep) id++;
			break;
		}
		ret *= 10ll;
		ret+=x[id]-'0';
		id++;
	}
	id++;
	return ret;
}

string get_string(string x, int &id, char sep=','){
	string ret = "";
	while(id < x.size()){
		if(x[id] == sep && sep ==',') break;
		if(x[id] == sep && (id+1 >= x.size() || x[id+1] != sep)) break;
		if(x[id] == sep){
			id+=2;
			continue;
		}
		if(x[id] >= 'A' && x[id] <= 'Z') x[id] = x[id] - 'A' + 'a';
		ret+=x[id];
		id++;
	}
	id++;
//	cout << ret << endl;
	return ret;
}

bool cari(string src, string pat){
	for(int i=0;i<pat.size();i++){
		if(src[src.size()-pat.size()+i] != pat[i]) return 0;
	}
	return 1;
}

int get_address(string x, int &id){
	string cur = "";
	if(x[id] == '"'){
		id++;
		cur = get_string(x,id,x[id-1]);
		id++;
	} else {
		cur = get_string(x,id);
	}
	int ret = -1;
	for(int i=0;i<4;i++){
		if(cari(cur,city[i])){
			ret = i;
			break;
		}
	}
	return ret;
}

string toString(char *x){
	string ret = "";
	int pan = strlen(x);
	for(int i=0;i<pan;i++){
		ret += x[i];
	}
	return ret;
}

int toNum(string x){
	int ret = 0;
	for(int i=0;i<x.size();i++){
		ret *= 10;
		ret += x[i] - '0';
	}
	return ret;
}

map<string,int> hari;

datim get_time(ll x){
	time_t rawtime = x;
  struct tm  ts;
  char       buf[80];

  ts = *gmtime(&rawtime);
  datim ret;

  strftime(buf, sizeof(buf), "%a", &ts);
  ret.type = hari[toString(buf)];

  strftime(buf, sizeof(buf), "%Y", &ts);
  ret.year = toNum(toString(buf));

  strftime(buf, sizeof(buf), "%m", &ts);
  ret.month = toNum(toString(buf));

  strftime(buf, sizeof(buf), "%d", &ts);
  ret.day = toNum(toString(buf));

  strftime(buf, sizeof(buf), "%H", &ts);
  ret.hour = toNum(toString(buf));

  strftime(buf, sizeof(buf), "%M", &ts);
  ret.minute = toNum(toString(buf));

  strftime(buf, sizeof(buf), "%S", &ts);
  ret.second = toNum(toString(buf));
  return ret;
}

datim add_eight_hour(datim x){
	x.hour+=8;
	if(x.hour >= 24){
		x.hour -= 24;
		x.day++;
		if(x.day > 31){
			x.month++;
			x.day -= 31;
		}
		x.type = (x.type+1)%7;
	}
	return x;
}

datim add_one_day(datim x){
	x.day++;
	if(x.day > 31){
		x.month++;
		x.day -= 31;
	}
	x.type = (x.type+1)%7;
	return x;
}

bool same_day(datim a, datim b){
	return a.month == b.month && a.day == b.day;
}

bool is_holiday(datim a){
	return a.type == 0 || (a.day == 25 && a.month == 3) || (a.day == 30 && a.month == 3) || (a.day == 31 && a.month == 3);
}

int dif(datim a, datim b){
	a = add_eight_hour(a);
	b = add_eight_hour(b);
	int cnt = 0;
	while(!same_day(a, b)){
		a = add_one_day(a);
		if(!is_holiday(a)) cnt++;
	}
	return cnt;
}

data split(string x){
	int id = 0;
	data ret;
	ret.orderId = get_num(x,id);
	
	ret.pick = get_time(get_num(x,id));
	
	ret.send1 = get_time(get_num(x,id));
	
	ll tmp2 = get_num(x,id);
	if(tmp2 == 0) ret.send2 = ret.send1;
	else ret.send2 = get_time(tmp2);
	
	ret.arr1 = dif(ret.pick, ret.send1);
	ret.arr2 = dif(ret.send1, ret.send2);
	
	ret.buyer = get_address(x,id);
	
	ret.seller = get_address(x,id);

	return ret;
}

vector<data> read_csv(){
	vector<data> ret;
	
	fstream fin;
	
	fin.open("dataset/delivery_orders_march.csv", ios::in);
	
	
	data row;
	string tmp;
	int cnt = 0;
	
	getline(fin,tmp);
	
	while(getline(fin,tmp)){
        if (tmp.back() == '\r') tmp.pop_back(); // additional to work perfectly in *nix system
		row = split(tmp);
		ret.push_back(row);
		
	}
	
	return ret;
}

vector<data> now;

void create_ans(){
	fstream fout;
	
	fout.open("result/answer.csv",ios::out | ios::app);
	
	fout << "orderid,is_late\n";
	
	for(int i=0;i<now.size();i++){
		fout << now[i].orderId << ",";
		if(now[i].isLate == 0) fout << "0";
		else{
			fout << "1";
		}
		fout << "\n";
	}
	return;
}

int main(){
	hari["Sun"] = 0;
	hari["Mon"] = 1;
	hari["Tue"] = 2;
	hari["Wed"] = 3;
	hari["Thu"] = 4;
	hari["Fri"] = 5;
	hari["Sat"] = 6;
	now = read_csv();
	for(int i=0;i<now.size();i++){
		data cur = now[i];
		if(cur.arr1 > sla[cur.seller][cur.buyer] || cur.arr2 > 3) now[i].isLate = 1;
		else now[i].isLate = 0;
	}
	create_ans();
	return 0;
}


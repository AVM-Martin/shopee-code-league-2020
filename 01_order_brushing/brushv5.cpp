//0.98729
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll THRESHOLD = 60*60;

struct data{
	ll orderId, shopId, userId, eventTime;
	
	void print(){
		printf("ORDERID = %lld, SHOPID = %lld, USERID = %lld, EVENTTIME = %lld\n",
		orderId, shopId, userId, eventTime);
	}
	
};

struct data_ans{
	ll shopId, userId;
};

bool cmp(data a, data b){
	if(a.shopId == b.shopId){
		if(a.eventTime == b.eventTime){
			return a.userId < b.userId;
		}
		return a.eventTime < b.eventTime;
	}
	return a.shopId < b.shopId;
}

inline ll dateToInt(ll m, ll d, ll y) {
	return 1461ll * (y + 4800ll + (m - 14ll) / 12ll) / 4ll +
		367ll * (m - 2ll - (m - 14ll) / 12ll * 12ll) / 12ll -
		3ll * ((y + 4900ll + (m - 14ll) / 12ll) / 100ll) /
4ll + d - 32075ll;
}


ll get_num(string x, int &id, char sep=','){
	ll ret = 0ll;
	while(id < x.size()){
		if(x[id] == sep) break;
		ret *= 10ll;
		ret+=x[id]-'0';
		id++;
	}
	id++;
	return ret;
}

ll get_time(string x, int &id){
	ll ret = 0ll;
	ll y = get_num(x,id,'-');
	ll m = get_num(x,id,'-');
	ll d = get_num(x,id,' ');
	ret = dateToInt(m,d,y);
	ret *=24ll;
	ret += get_num(x,id,':');
	ret *=60ll;
	ret += get_num(x,id,':');
	ret *=60ll;
	ret += get_num(x,id,'\n');
	return ret;
}

data split(string x){
	int id = 0;
	data ret;
	ret.orderId = get_num(x,id);
//	cout << ret.orderId << "<\n";
	ret.shopId = get_num(x,id);
//	cout << ret.shopId << "<<\n";
	ret.userId = get_num(x,id);
//	cout << ret.userId << "<<<\n";
	ret.eventTime = get_time(x,id);
//	cout << ret.eventTime << "<<<<\n";
	return ret;
}

vector<data> read_csv(){
	vector<data> ret;
	
	fstream fin;
	
	fin.open("dataset/order_brush_order.csv", ios::in);
	
	
	data row;
	string tmp;
	int cnt = 0;
	
	getline(fin,tmp);
	
	while(getline(fin,tmp)){
//		cout << tmp << endl;
		row = split(tmp);
		ret.push_back(row);
//		printf("PUSH : ");
//		row.print();
	}
	
	return ret;
}

map<ll,int> cnt;
vector<data_ans> res;
vector<data> now;
map<ll,set<ll> > ans;

set<int> list_id;

void proc(int l, int r){
	ll bef = -THRESHOLD;
	list_id.clear();
	int id = l;
	while(l<=r){
		while(id <= r && now[id].eventTime - now[l].eventTime <= THRESHOLD){
			cnt[now[id].userId]++;
			id++;
			ll kiri = id-l;
			ll kanan = 3ll * (ll)cnt.size();
			ll aft = now[id-1].eventTime+THRESHOLD;
			if(id <= r){
				aft = now[id].eventTime-1;
			}
			if(kanan <= kiri && (aft - bef >= THRESHOLD)){
				int lst = 0;
				for(auto x : cnt){
					if(x.second > lst) lst = x.second;
				}
				for(int i=l;i<id;i++){
					if(cnt[now[i].userId] == lst) list_id.insert(i);
				}
			}
		}
//		cnt[now[l].userId]--;
//		if(cnt[now[l].userId] == 0) cnt.erase(now[l].userId);
		bef = now[l].eventTime+1;
		l++;
		id = l;
		cnt.clear();
	}
	cnt.clear();
	int lst = 0;
	for(auto x : list_id){
		cnt[now[x].userId]++;
		lst = max(lst,cnt[now[x].userId]);
	}
	for(auto x : cnt){
		if(x.second == lst) ans[now[r].shopId].insert(x.first);
	}
	return;
}

void create_ans(){
	fstream fout;
	
	fout.open("result/answer.csv",ios::out | ios::app);
	
	fout << "shopid,userid\n";
	
	for(int i=0;i<now.size();i++){
		data_ans cur;
		if(i==0 || now[i].shopId != now[i-1].shopId){
			fout << now[i].shopId << ",";
			if(ans[now[i].shopId].size() == 0) fout << "0";
			else{
				bool dan = 0;
				for(auto x : ans[now[i].shopId]){
					if(dan) fout << "&";
					fout << x;
					dan = 1;
				}
			}
			fout << "\n";
		}
	}
	return;
}

int main(){
	now = read_csv();
	sort(now.begin(),now.end(),cmp);
//	ll maksi = now[0].eventTime;
//	ll mini = now[0].eventTime;
//	for(int i=0;i<now.size();i++){
//		maksi = max(maksi,now[i].eventTime);
//		mini = min(mini,now[i].eventTime);
//	}
//	printf("%lld - %lld = %lld\n",mini,maksi, maksi - mini);
	int l=0;
	for(int i=1;i<now.size();i++){
		if(now[i].shopId != now[l].shopId){
			cnt.clear();
			proc(l,i-1);
			l = i;
		}
	}
	cnt.clear();
	proc(l,now.size()-1);
	create_ans();
	return 0;
}


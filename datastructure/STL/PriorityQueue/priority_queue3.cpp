struct Custom{

	int x;
	int y;
	int value;
	Custom(int value) : x(0), y(0), value(value) {
    }

};


struct cmp{
    bool operator()(Custom t, Custom u){
        return t.value > u.value;
    }
};



int main(){

	// priority_queue
	priority_queue< Custom, vector<Custom>,  cmp > pq;


	// push(element)
	pq.push(Custom(5));
	pq.push(Custom(2));
	pq.push(Custom(8));
	pq.push(Custom(9));
	pq.push(Custom(1));
	pq.push(Custom(14));


	// pop()
	pq.pop();
	pq.pop();


	// top();
	cout << "pq top : " << pq.top().value << '\n';


	// empty(), size()
	if(!pq.empty()) cout << "pq size : " << pq.size() << '\n';


	// pop all
	while(!pq.empty()){
		cout << pq.top().value << " ";
		pq.pop();
	}

	cout << '\n';

	return 0;

}
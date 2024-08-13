#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

class ScrollType
{
public :
	int index;// 索引
	string srcData;// 原始資料
	// --------------------------------------------------------
	// 學校代碼	學校名稱	科系代碼	科系名稱	日間∕進修別	等級別	學生數	教師數	上學年度畢業生數	縣市名稱	體系別
	int schoolCode; //		學校代碼
	string schoolName; //	學校名稱
	int departmentCode; //	科系代碼
	string departmentName; //	科系名稱
	string dayFurtherStudy; //	日間∕進修別
	string level; //		等級別
	int numberOfStudents; //	學生數
	string numberOfTeachers;     //	教師數
	int numberOfGraduatesLastYear; //		上學年度畢業生數
	int countyAndCityName; //	縣市名稱
	string systemType;     //	體系別
public :
	ScrollType( int srcIndex , const string& src , const vector<string>& vec )
			: index( srcIndex ) , srcData( src ) //
			, schoolCode( atoi( vec[0].c_str() ) ) //
			, schoolName( vec[1] ) //
			, departmentCode( atoi( vec[2].c_str() ) ) //	科系代碼
			, departmentName( vec[3] ) //	科系名稱
			, dayFurtherStudy( vec[4] ) //	日間∕進修別
			, level( vec[5] ) // 等級別
			, numberOfStudents( atoi( vec[6].c_str() ) ) //	學生數
			, numberOfTeachers( vec[7] )     //	教師數
			, numberOfGraduatesLastYear( atoi( vec[8].c_str() ) ) // 上學年度畢業生數
			, countyAndCityName( atoi( vec[9].c_str() ) )//	縣市名稱
			, systemType( vec[10] )//	體系別
	{

	}
};

class ClassList
{
	// 數據記錄集
	vector<ScrollType> scrollVec;

	// 用於構成檔名的數位
	string fileNO;
public :
	// 取資料
	const ScrollType& operator[]( const int index ) const;

public:
	// 建構
	ClassList();

	// 解構
	~ClassList();

	// 讀檔
	bool readF( const int defFileIndex = 0 );

	// 是否為空
	bool isEmpty() const;

	// 取大小
	int size() const;

	// 清空
	void clearUp();

	// 字串分格
	static vector<string> split( const string str , const char key );
};

// 載入 csv
vector<string> ClassList::split( const string str , const char key )
{
	string temp = "";
	vector<string> ret;
	int i;

	i = 0;
	while( str[i] != 0 )
	{
		if( str[i] == key )
		{
			ret.push_back( temp );
			temp = "";
		}else
		{
			temp += str[i];
		}
		i++;
	}
	ret.push_back( temp );
	return ret;
}

// 載入檔案
bool ClassList::readF( const int defFileIndex )
{
	int fileIndex; // 檔案索引
	char fileName[1024];
	char ch[1024];
	const char * str;
	int index = 0;


	// 1. 清空
	clearUp();
	// 2. 如果未指定載入的檔案編號
	loop_enter_id :
	if( defFileIndex == 0 )
	{
		// 2.1 提示要求輸入檔案編號
		cout << "Input a file number ([0] Quit): ";

		cin >> ch;
		if( strcmp( ch , "0" ) == 0 )
			return false ;
	/*
		// 2.2 如果是 0 就離開
		if( fileIndex == 0 )
			return false;*/
	}else
	{
		// 2.3 如果有預設值，就指定為載入檔案
		fileIndex = defFileIndex;
		sprintf( ch , "%d" , defFileIndex );
	}

	// 3. 載入檔案
	sprintf( fileName , "input%s.txt" , ch );
	FILE * file = fopen( fileName , "r" );
	// 4. 如果載入失敗，就噴錯並離開
	if( file == NULL )
	{
		cout << "### " << fileName << " does not exist! ###" << endl ;
		goto loop_enter_id ;
		return false;
	}

	// 5.去標題行
	fgets( ch , sizeof( ch ) , file );
	// 6. 一行一行讀到檔案最後
	while( true )
	{
		vector<string> vec;

		// 6.1 讀一行
		ch[0] = 0;
		fgets( ch , sizeof( ch ) , file );
		// 6.2 如果讀失敗就離開
		if( ch[0] == 0 )
			break;

		// 6.3 去掉換行符號
		str = strtok( ch , "\r\n" );
		const string srcData( ch );
		// 6.4 字串分解，以 tab 分解成 vector
		vec = split( str , '\t' );
		// 6.5 如果資料小於 11 欄，就結束
		if( vec.size() < 11 )
		{
			break;
		}
		// 6.6 放到陣列中
		index++;
//		if( index >= 5860 )
//			index = 5860 ;
		scrollVec.push_back( ScrollType( index , srcData , vec ) );


	}
//	const ScrollType& ct = scrollVec[4196];
	// 7. 關檔
	fclose( file );
	// 8. 如果沒有資料，就噴錯並回傳 false
	if( scrollVec.size() == 0 )
	{
		cout << "There is no data!" << endl << endl;
		return false;
	}
	// 9. 完成
	return true;
}

ClassList::~ClassList()
{
	clearUp();
}

void ClassList::clearUp()
{
	scrollVec.clear();
	fileNO.clear();
}

int ClassList::size() const
{
	return scrollVec.size();
}

ClassList::ClassList() : fileNO( "" )
{
}

bool ClassList::isEmpty() const
{
	return ( !scrollVec.size() );
}

const ScrollType& ClassList::operator[]( const int index ) const
{
	return scrollVec[index];
}

class HEAP
{
protected:
	// 聲明堆節點的類型
	typedef struct hT
	{

		// 記錄標識碼
		int key;
		// 比較的關鍵
		int rid;
	} heapType;


	// 用於保留堆節點的陣列
	heapType * _hArray;

	// 當前節點數
	int _count;

	// 交換次數
	int _sortCount;
public:
	//  構造 函數
	HEAP( int NO );

	HEAP();

	~HEAP();

	// 檢查它是否為空堆
	bool isEmpty();

	// 顯示三個節點的內容
	void showNODES();

	// 將一條記錄插入堆中
	void
	insert( int index , int numberOfStudents );

	// 結束清理
	void clearUp();

	double getSpeed() const;
};

// 將一條記錄插入堆中
void HEAP::insert( int index , int numberOfStudents )
{

	int i;
	heapType ht;

	ht.key = numberOfStudents;
	ht.rid = index;


	i = ++( _count );

	while( ( i != 1 ) && ( ht.key > _hArray[i / 2].key ) )
	{
		_hArray[i] = _hArray[i / 2];
		i /= 2;
		// 交換
		_sortCount++;
	}
	_hArray[i] = ht;
}

// 顯示三個節點的內容
void HEAP::showNODES()
{

	int leftmost , p;
	heapType * pht;
	cout << "<max heap>" << endl;
	pht = &this->_hArray[1];
	cout << "root: [" << pht->rid << "] " << pht->key << endl;
	pht = &this->_hArray[_count];
	cout << "bottom: [" << pht->rid << "] " << pht->key << endl;

	//
	leftmost = 0;
	p = 1;
	while( p <= _count )
	{
		leftmost = p;
		p = p * 2;
	}
	pht = &this->_hArray[leftmost];
	cout << "leftmost bottom: [" << pht->rid << "] " << pht->key << endl;
}

HEAP::~HEAP()
{
	clearUp();
}

// 刪除物件內容
void HEAP::clearUp()
{
	if( _hArray != NULL )
		delete[] _hArray;
	_hArray = NULL;
	_count = 0;
}

HEAP::HEAP() //
		: _hArray( NULL ) //
		, _count( 0 )//
		, _sortCount( 0 )//
{
}

// 構造函數
HEAP::HEAP( int NO )
		: _count( 0 ) //
		, _sortCount( 0 )//
{
	try
	{
		// 動態分配的陣列
		_hArray = new heapType[NO * 4];
	}
	catch( std::bad_alloc& ba )
	// 無法分配動態空間
	{
		std::cerr << endl << "bad_alloc caught: " << ba.what() << endl;
	}
}

bool HEAP::isEmpty()
{
	return ( !_count );
}

double HEAP::getSpeed() const
{
	if( _count == 0 )
		return 0;
	const double speed = _sortCount;
	const double count = _count - 2;

	return speed / count;
	return 0;
}

class DEAP
{
protected:
	// 聲明堆節點的類型
	typedef struct hT
	{
		int rid; // 記錄標識碼
		int key; // 比較的關鍵
		const ScrollType * ct;
	} heapType;

private :
	// 當前節點數
	int _count;
	// 用於保留堆節點的陣列
	heapType * _hArray;

	// 交換次數
	int _sortCount;

public:
	// 構造函數
	DEAP( int count );

	// 解構
	~DEAP();

	// 取得
	const ScrollType& operator[]( const int index ) const;

	// 檢查它是否為空堆
	bool isEmpty();

	// 將一條記錄插入堆中
	void insert( int index , int numberOfStudents , const ScrollType * ct );


	void showNodes() const;

	// 清空
	void clearUp();

	// 向上更新
	void VerifyMin( int index , heapType ht );

	void VerifyMax( int index , heapType ht );

	void maxHeapify( int index );

	void setSize( int count );

	int size() const;

	const ScrollType * popMax();

	double getSpeed() const;
};

// 最小堆排序
void DEAP::VerifyMin( int index , heapType ht )
{
	// 1. 與自已的上面並較，如果比較小就交換，
	while( ( index > 3 ) && ( ht.key < _hArray[index / 2].key ) )
	{
		_sortCount++;
		_hArray[index] = _hArray[index / 2];
		index /= 2;
	}
	// 2. 放到最後的索引
	_hArray[index] = ht;
}

// 最大堆排序
void DEAP::VerifyMax( int index , heapType ht )
{
	// 1. 與自已的上面並較，如果比較大就交換，
	while( ( index > 3 ) && ( ht.key > _hArray[index / 2].key ) )
	{
		_sortCount++;
		_hArray[index] = _hArray[index / 2];
		index /= 2;
	}
	// 2. 放到最後的索引
	_hArray[index] = ht;
}

// 堆化（heapify）函數
void DEAP::maxHeapify( int index )
{
	// 1. 找出下一階的左右索引
	int leftChild = 2 * index;
	int rightChild = 2 * index + 1;
	int largest = index;

	// 2. 判斷這個數是否大於下一階的左邊，是的話就更新
	if( leftChild < _count && _hArray[leftChild].key > _hArray[largest].key )
		largest = leftChild;
	// 3. 判斷這個數是否大於下一階的左邊，是的話就更新
	if( rightChild < _count && _hArray[rightChild].key > _hArray[largest].key )
		largest = rightChild;
	// 4. 如果與輸入的索引不相同
	if( largest != index )
	{
		// 4.1 進行交換
		std::swap( _hArray[index] , _hArray[largest] );
		// 4.2 再往下一層比對
		maxHeapify( largest );
	}
}

// 加入一筆資料
void DEAP::insert( int index , int numberOfStudents , const ScrollType * ct )
{

	int i , j;
	heapType ht;
	int minHeap , height , p;
	// 1. 放到資料索引中
	ht.key = numberOfStudents;
	ht.rid = index;
	ht.ct = ct;
	// 2. 加到最下面
	if( _count < 1 )
		_count = 1;
	i = ++( _count );
	_hArray[i] = ht;
	// 3. 如果是第一筆，就離開
	if( i == 2 )return;
	//
	height = 1;
	minHeap = 2;
	p = 2;
	// 4. 判斷最深的地方
	while( true )
	{
		// 4.1 如果目前索引在這一階中，就跳出迴圈
		if( ( i >= minHeap ) && ( i < ( minHeap + p ) ) )
			break;
		// 4.2 下一階的索引
		minHeap += p;
		// 4.3 下一階的數量
		p *= 2;
		// 4.4 下一階的深度
		height++;
	}
	// 5. 由於分大小，所以將數量 / 2
	p /= 2;
	// 6 判斷這一階是左邊還是右邊
	// 6.1 左邊
	if( i < ( minHeap + p ) )
	{
		// 6.1 是否比上一階的大
		j = ( i + p ) / 2;
		if( ht.key > _hArray[j].key )
		{
			// 6.1.1 交換
			_hArray[i] = _hArray[j];
			_sortCount++;
			// 6.1.2 大堆排序(右邊)
			VerifyMax( j , ht );
		}else
		{
			// 6.1.3 否則就小堆排序
			VerifyMin( i , ht );
		}

	}else // 6.2 右
	{
		// 6.2.1 判斷是否比同一位的左邊大
		j = i - p;
		if( ht.key < _hArray[j].key )
		{
			// 6.2.2 是的話就交換
			_hArray[i] = _hArray[j];
			_sortCount++;
			// 6.2.3 做最小堆排序
			VerifyMin( j , ht );
		}else
		{
			// 6.2.4 做最大堆排序
			VerifyMax( i , ht );
		}
	}

}

void DEAP::showNodes() const
{

	int leftmost , p;
	heapType * pht;
	cout << "<DEAP>" << endl;

	pht = &this->_hArray[_count];
	cout << "bottom: [" << pht->rid << "] " << pht->key << endl;

	//
	leftmost = 0;
	p = 2;
	while( p <= _count )
	{
		leftmost = p;
		p = p * 2;
	}
	pht = &this->_hArray[leftmost];
	cout << "leftmost bottom: [" << pht->rid << "] " << pht->key << endl;
}

bool DEAP::isEmpty()
{
	return ( !_count );
}

void DEAP::clearUp()
{
	// 1. 如果陣列有資料，就移除
	if( _hArray != NULL )
		delete[] _hArray;
	// 2. 資料清為 NULL
	_hArray = NULL;
	_count = 0;
}

DEAP::~DEAP()
{
	clearUp();
}

// 建構
DEAP::DEAP( int count )//
		: _count( 0 )//
		, _sortCount( 0 )//
{
	setSize( count );

}

void DEAP::setSize( int count )
{
	try
	{
		// 建立資料最大值的4倍的數據，以免超出範圍
		_count = 0;
		_hArray = new heapType[count * 4];
	}
	catch( std::bad_alloc& ba )
	{
		std::cerr << endl << "bad_alloc caught: " << ba.what() << endl;
	}
}

int DEAP::size() const
{
	return _count;
}

// 取一個最大值
const ScrollType * DEAP::popMax()
{
	int leftmost;
	int p;

	// 1. 如果剩餘數小於 2 個，就回傳 NULL
	if( _count < 2 )
		return NULL;
	// 2. 如果數量 == 2 ，就回傳索引 2 的
	if( _count == 2 )
	{
		heapType ht = this->_hArray[2];
		_count--;
		return ht.ct;
	}
	// 3. 取得最大值(索引3)的資料
	heapType ht = this->_hArray[3];
	// 4. 數量 -1
	_count--;

	// 測試用
	if( 0 )
	{
		//

		leftmost = 0;
		p = 2;
		while( p <= _count )
		{
			leftmost = p;
			p = p * 2;
		}
		leftmost--;

		const heapType a = this->_hArray[_count];
		const heapType b = this->_hArray[leftmost];
		if( 0 )
			if( a.key > b.key )
			{
				this->_hArray[_count] = b;
				this->_hArray[leftmost] = a;
			}
	}

	// 5. 把最後一個搬最索引 3 的位置
	this->_hArray[3] = this->_hArray[_count];
	// 6. 開始向下沈
	maxHeapify( 3 );
	// 7. 回傳所取得的資料
	return ht.ct;
}

const ScrollType& DEAP::operator[]( const int index ) const
{
	return *_hArray[index].ct;
}

double DEAP::getSpeed() const
{
	if( _count == 0 )
		return 0;
	const double speed = _sortCount;
	const double count = _count - 2;

	return speed / count;
}

// 執行 1. Build a min heap
void runMenu1( ClassList& aList )
{
	if( aList.readF() )
	{
		HEAP aHeap( aList.size() );

		for( int i = 0 ; i < aList.size() ; ++i )
		{
			const ScrollType& ct = aList[i];
			aHeap.insert( ct.index , ct.numberOfStudents );
		}
		aHeap.showNODES();
	}
}

// 執行 2. Build a DEAP
void runMenu2( DEAP& aDeap , ClassList& aList )
{
	int i;
	// 1. 載入檔案
	if( aList.readF() )
	{
		// 2. 清空 deap 讀資料
		aDeap.clearUp();
		// 3. 設定 deap 最大陣列大小
		aDeap.setSize( aList.size() );
		// 4. 將載入的資料一筆筆寫到 deap 中
		for( i = 0 ; i < aList.size() ; ++i )
		{
			const ScrollType& ct = aList[i];
			aDeap.insert( ct.index , ct.numberOfStudents , &ct );
		}
		// 5. 繪製題目要的輸出資料
		aDeap.showNodes();
	}
}

// 執行 3. 3: Top-K maximums from DEAP
void runMenu3( DEAP& aDeap , const ClassList& aList )
{
	char ch[1024];
	int i;
	int command = 0;
	// 沒有就離開
	if( aList.isEmpty() )
		return;
	// 1. 提示並要求輸入 K 值(要取的數量)
	cout << endl << "Enter the value of K in [1, " << aDeap.size() - 1 << "]: ";
	cin >> command;

	// 2. 輸入值如果超出範例就噴錯離開
	if( ( command <= 0 ) || ( command >= aDeap.size() ) )
	{
		// cout << "enter K error" << endl;
		return;
	}
	//
	/*
	// test
	for( i = 2 ; i <= 50 ; ++i )
	{
		const ScrollType& data = aDeap[i] ;

		sprintf( ch , "Top    %2d :[%4d] %s%s,%s,%s,%d\n" , ( i + 1 ) , data.index , data.schoolName.c_str() ,
				data.departmentName.c_str() , data.dayFurtherStudy.c_str() , data.level.c_str() ,
				data.numberOfStudents );
		cout << ch;
	}
	cout << endl ;*/
	// 3. 輸出取最大值
	for( i = 0 ; i < command ; ++i )
	{
		// 3.1 pop 一個最大值出來
		const ScrollType * pct = aDeap.popMax();
		// 3.2 如果資料是空的，就重來
		if( pct == NULL )continue;
		// 3.3 印出資料
		const ScrollType& data = *pct;

		sprintf( ch , "Top%4d: [%d] %s%s, %s, %s, %d\n" , ( i + 1 ) , data.index , data.schoolName.c_str() ,
				data.departmentName.c_str() , data.dayFurtherStudy.c_str() , data.level.c_str() ,
				data.numberOfStudents );
		cout << ch;
	}
}

// 測試用的 4
void runMenu4()
{
	const int fileIndex[] = { 101 , 102 , 103 , 104 , 0 };
	int i , k;
	for( i = 0 ; fileIndex[i] != 0 ; ++i )
	{
		ClassList aList;
		if( aList.readF( fileIndex[i] ) )
		{
			HEAP aHeap( aList.size() );
			DEAP aDeap( aList.size() );
			for( k = 0 ; k < aList.size() ; ++k )
			{
				const ScrollType& ct = aList[k];
				aHeap.insert( ct.index , ct.numberOfStudents );
				aDeap.insert( ct.index , ct.numberOfStudents , &ct );
			}
			printf( "Index: %d, Heap:%.2lf , Deap: %.2lf\n" , fileIndex[i] , aHeap.getSpeed() , aDeap.getSpeed()
			);
		}else
		{
			cout << "load file error: " << fileIndex[i] << endl;
		}
	}
}

//
int main( void )
{
	int command = 0;
	ClassList aList;
	DEAP deap( 0 );

	do
	{
		cout << endl << "**** Heap Construction ********";
		cout << endl << "* 0. QUIT                     *";
		cout << endl << "* 1. Build a max heap         *";
		cout << endl << "* 2. Build a DEAP             *";
		cout << endl << "* 3. Top-K maximums from DEAP *";
		cout << endl << "*******************************";
		cout << endl << "Input a choice(0, 1, 2, 3): ";

		cin >> command;
		switch( command )
		{
		case 0:
			break;
		case 1:
			runMenu1( aList );
			break;
		case 2: // 1 下載入 deap 指令
			runMenu2( deap , aList );
			break;
		case 3: // 2. 找出Deap 前K組最大的數值，
			runMenu3( deap , aList );
			break;
		case -1234 :
			runMenu4();
			// break ;
		default:
			cout << endl << "Command does not exist!" << endl;
		}   // end switch
	}while( command != 0 );
	aList.clearUp();
//	system( "pause" );
	return 0;
}   // end main

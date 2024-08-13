#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

class ScrollType
{
public :
	int index;// ����
	string srcData;// ��l���
	// --------------------------------------------------------
	// �ǮեN�X	�ǮզW��	��t�N�X	��t�W��	�鶡�A�i�קO	���ŧO	�ǥͼ�	�Юv��	�W�Ǧ~�ײ��~�ͼ�	�����W��	��t�O
	int schoolCode; //		�ǮեN�X
	string schoolName; //	�ǮզW��
	int departmentCode; //	��t�N�X
	string departmentName; //	��t�W��
	string dayFurtherStudy; //	�鶡�A�i�קO
	string level; //		���ŧO
	int numberOfStudents; //	�ǥͼ�
	string numberOfTeachers;     //	�Юv��
	int numberOfGraduatesLastYear; //		�W�Ǧ~�ײ��~�ͼ�
	int countyAndCityName; //	�����W��
	string systemType;     //	��t�O
public :
	ScrollType( int srcIndex , const string& src , const vector<string>& vec )
			: index( srcIndex ) , srcData( src ) //
			, schoolCode( atoi( vec[0].c_str() ) ) //
			, schoolName( vec[1] ) //
			, departmentCode( atoi( vec[2].c_str() ) ) //	��t�N�X
			, departmentName( vec[3] ) //	��t�W��
			, dayFurtherStudy( vec[4] ) //	�鶡�A�i�קO
			, level( vec[5] ) // ���ŧO
			, numberOfStudents( atoi( vec[6].c_str() ) ) //	�ǥͼ�
			, numberOfTeachers( vec[7] )     //	�Юv��
			, numberOfGraduatesLastYear( atoi( vec[8].c_str() ) ) // �W�Ǧ~�ײ��~�ͼ�
			, countyAndCityName( atoi( vec[9].c_str() ) )//	�����W��
			, systemType( vec[10] )//	��t�O
	{

	}
};

class ClassList
{
	// �ƾڰO����
	vector<ScrollType> scrollVec;

	// �Ω�c���ɦW���Ʀ�
	string fileNO;
public :
	// �����
	const ScrollType& operator[]( const int index ) const;

public:
	// �غc
	ClassList();

	// �Ѻc
	~ClassList();

	// Ū��
	bool readF( const int defFileIndex = 0 );

	// �O�_����
	bool isEmpty() const;

	// ���j�p
	int size() const;

	// �M��
	void clearUp();

	// �r�����
	static vector<string> split( const string str , const char key );
};

// ���J csv
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

// ���J�ɮ�
bool ClassList::readF( const int defFileIndex )
{
	int fileIndex; // �ɮׯ���
	char fileName[1024];
	char ch[1024];
	const char * str;
	int index = 0;


	// 1. �M��
	clearUp();
	// 2. �p�G�����w���J���ɮ׽s��
	loop_enter_id :
	if( defFileIndex == 0 )
	{
		// 2.1 ���ܭn�D��J�ɮ׽s��
		cout << "Input a file number ([0] Quit): ";

		cin >> ch;
		if( strcmp( ch , "0" ) == 0 )
			return false ;
	/*
		// 2.2 �p�G�O 0 �N���}
		if( fileIndex == 0 )
			return false;*/
	}else
	{
		// 2.3 �p�G���w�]�ȡA�N���w�����J�ɮ�
		fileIndex = defFileIndex;
		sprintf( ch , "%d" , defFileIndex );
	}

	// 3. ���J�ɮ�
	sprintf( fileName , "input%s.txt" , ch );
	FILE * file = fopen( fileName , "r" );
	// 4. �p�G���J���ѡA�N�Q�������}
	if( file == NULL )
	{
		cout << "### " << fileName << " does not exist! ###" << endl ;
		goto loop_enter_id ;
		return false;
	}

	// 5.�h���D��
	fgets( ch , sizeof( ch ) , file );
	// 6. �@��@��Ū���ɮ׳̫�
	while( true )
	{
		vector<string> vec;

		// 6.1 Ū�@��
		ch[0] = 0;
		fgets( ch , sizeof( ch ) , file );
		// 6.2 �p�GŪ���ѴN���}
		if( ch[0] == 0 )
			break;

		// 6.3 �h������Ÿ�
		str = strtok( ch , "\r\n" );
		const string srcData( ch );
		// 6.4 �r����ѡA�H tab ���Ѧ� vector
		vec = split( str , '\t' );
		// 6.5 �p�G��Ƥp�� 11 ��A�N����
		if( vec.size() < 11 )
		{
			break;
		}
		// 6.6 ���}�C��
		index++;
//		if( index >= 5860 )
//			index = 5860 ;
		scrollVec.push_back( ScrollType( index , srcData , vec ) );


	}
//	const ScrollType& ct = scrollVec[4196];
	// 7. ����
	fclose( file );
	// 8. �p�G�S����ơA�N�Q���æ^�� false
	if( scrollVec.size() == 0 )
	{
		cout << "There is no data!" << endl << endl;
		return false;
	}
	// 9. ����
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
	// �n����`�I������
	typedef struct hT
	{

		// �O�����ѽX
		int key;
		// ���������
		int rid;
	} heapType;


	// �Ω�O�d��`�I���}�C
	heapType * _hArray;

	// ��e�`�I��
	int _count;

	// �洫����
	int _sortCount;
public:
	//  �c�y ���
	HEAP( int NO );

	HEAP();

	~HEAP();

	// �ˬd���O�_���Ű�
	bool isEmpty();

	// ��ܤT�Ӹ`�I�����e
	void showNODES();

	// �N�@���O�����J�襤
	void
	insert( int index , int numberOfStudents );

	// �����M�z
	void clearUp();

	double getSpeed() const;
};

// �N�@���O�����J�襤
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
		// �洫
		_sortCount++;
	}
	_hArray[i] = ht;
}

// ��ܤT�Ӹ`�I�����e
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

// �R�����󤺮e
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

// �c�y���
HEAP::HEAP( int NO )
		: _count( 0 ) //
		, _sortCount( 0 )//
{
	try
	{
		// �ʺA���t���}�C
		_hArray = new heapType[NO * 4];
	}
	catch( std::bad_alloc& ba )
	// �L�k���t�ʺA�Ŷ�
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
	// �n����`�I������
	typedef struct hT
	{
		int rid; // �O�����ѽX
		int key; // ���������
		const ScrollType * ct;
	} heapType;

private :
	// ��e�`�I��
	int _count;
	// �Ω�O�d��`�I���}�C
	heapType * _hArray;

	// �洫����
	int _sortCount;

public:
	// �c�y���
	DEAP( int count );

	// �Ѻc
	~DEAP();

	// ���o
	const ScrollType& operator[]( const int index ) const;

	// �ˬd���O�_���Ű�
	bool isEmpty();

	// �N�@���O�����J�襤
	void insert( int index , int numberOfStudents , const ScrollType * ct );


	void showNodes() const;

	// �M��
	void clearUp();

	// �V�W��s
	void VerifyMin( int index , heapType ht );

	void VerifyMax( int index , heapType ht );

	void maxHeapify( int index );

	void setSize( int count );

	int size() const;

	const ScrollType * popMax();

	double getSpeed() const;
};

// �̤p��Ƨ�
void DEAP::VerifyMin( int index , heapType ht )
{
	// 1. �P�ۤw���W���ø��A�p�G����p�N�洫�A
	while( ( index > 3 ) && ( ht.key < _hArray[index / 2].key ) )
	{
		_sortCount++;
		_hArray[index] = _hArray[index / 2];
		index /= 2;
	}
	// 2. ���̫᪺����
	_hArray[index] = ht;
}

// �̤j��Ƨ�
void DEAP::VerifyMax( int index , heapType ht )
{
	// 1. �P�ۤw���W���ø��A�p�G����j�N�洫�A
	while( ( index > 3 ) && ( ht.key > _hArray[index / 2].key ) )
	{
		_sortCount++;
		_hArray[index] = _hArray[index / 2];
		index /= 2;
	}
	// 2. ���̫᪺����
	_hArray[index] = ht;
}

// ��ơ]heapify�^���
void DEAP::maxHeapify( int index )
{
	// 1. ��X�U�@�������k����
	int leftChild = 2 * index;
	int rightChild = 2 * index + 1;
	int largest = index;

	// 2. �P�_�o�ӼƬO�_�j��U�@��������A�O���ܴN��s
	if( leftChild < _count && _hArray[leftChild].key > _hArray[largest].key )
		largest = leftChild;
	// 3. �P�_�o�ӼƬO�_�j��U�@��������A�O���ܴN��s
	if( rightChild < _count && _hArray[rightChild].key > _hArray[largest].key )
		largest = rightChild;
	// 4. �p�G�P��J�����ޤ��ۦP
	if( largest != index )
	{
		// 4.1 �i��洫
		std::swap( _hArray[index] , _hArray[largest] );
		// 4.2 �A���U�@�h���
		maxHeapify( largest );
	}
}

// �[�J�@�����
void DEAP::insert( int index , int numberOfStudents , const ScrollType * ct )
{

	int i , j;
	heapType ht;
	int minHeap , height , p;
	// 1. ����Ư��ޤ�
	ht.key = numberOfStudents;
	ht.rid = index;
	ht.ct = ct;
	// 2. �[��̤U��
	if( _count < 1 )
		_count = 1;
	i = ++( _count );
	_hArray[i] = ht;
	// 3. �p�G�O�Ĥ@���A�N���}
	if( i == 2 )return;
	//
	height = 1;
	minHeap = 2;
	p = 2;
	// 4. �P�_�̲`���a��
	while( true )
	{
		// 4.1 �p�G�ثe���ަb�o�@�����A�N���X�j��
		if( ( i >= minHeap ) && ( i < ( minHeap + p ) ) )
			break;
		// 4.2 �U�@��������
		minHeap += p;
		// 4.3 �U�@�����ƶq
		p *= 2;
		// 4.4 �U�@�����`��
		height++;
	}
	// 5. �ѩ���j�p�A�ҥH�N�ƶq / 2
	p /= 2;
	// 6 �P�_�o�@���O�����٬O�k��
	// 6.1 ����
	if( i < ( minHeap + p ) )
	{
		// 6.1 �O�_��W�@�����j
		j = ( i + p ) / 2;
		if( ht.key > _hArray[j].key )
		{
			// 6.1.1 �洫
			_hArray[i] = _hArray[j];
			_sortCount++;
			// 6.1.2 �j��Ƨ�(�k��)
			VerifyMax( j , ht );
		}else
		{
			// 6.1.3 �_�h�N�p��Ƨ�
			VerifyMin( i , ht );
		}

	}else // 6.2 �k
	{
		// 6.2.1 �P�_�O�_��P�@�쪺����j
		j = i - p;
		if( ht.key < _hArray[j].key )
		{
			// 6.2.2 �O���ܴN�洫
			_hArray[i] = _hArray[j];
			_sortCount++;
			// 6.2.3 ���̤p��Ƨ�
			VerifyMin( j , ht );
		}else
		{
			// 6.2.4 ���̤j��Ƨ�
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
	// 1. �p�G�}�C����ơA�N����
	if( _hArray != NULL )
		delete[] _hArray;
	// 2. ��ƲM�� NULL
	_hArray = NULL;
	_count = 0;
}

DEAP::~DEAP()
{
	clearUp();
}

// �غc
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
		// �إ߸�Ƴ̤j�Ȫ�4�����ƾڡA�H�K�W�X�d��
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

// ���@�ӳ̤j��
const ScrollType * DEAP::popMax()
{
	int leftmost;
	int p;

	// 1. �p�G�Ѿl�Ƥp�� 2 �ӡA�N�^�� NULL
	if( _count < 2 )
		return NULL;
	// 2. �p�G�ƶq == 2 �A�N�^�ǯ��� 2 ��
	if( _count == 2 )
	{
		heapType ht = this->_hArray[2];
		_count--;
		return ht.ct;
	}
	// 3. ���o�̤j��(����3)�����
	heapType ht = this->_hArray[3];
	// 4. �ƶq -1
	_count--;

	// ���ե�
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

	// 5. ��̫�@�ӷh�̯��� 3 ����m
	this->_hArray[3] = this->_hArray[_count];
	// 6. �}�l�V�U�H
	maxHeapify( 3 );
	// 7. �^�ǩҨ��o�����
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

// ���� 1. Build a min heap
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

// ���� 2. Build a DEAP
void runMenu2( DEAP& aDeap , ClassList& aList )
{
	int i;
	// 1. ���J�ɮ�
	if( aList.readF() )
	{
		// 2. �M�� deap Ū���
		aDeap.clearUp();
		// 3. �]�w deap �̤j�}�C�j�p
		aDeap.setSize( aList.size() );
		// 4. �N���J����Ƥ@�����g�� deap ��
		for( i = 0 ; i < aList.size() ; ++i )
		{
			const ScrollType& ct = aList[i];
			aDeap.insert( ct.index , ct.numberOfStudents , &ct );
		}
		// 5. ø�s�D�حn����X���
		aDeap.showNodes();
	}
}

// ���� 3. 3: Top-K maximums from DEAP
void runMenu3( DEAP& aDeap , const ClassList& aList )
{
	char ch[1024];
	int i;
	int command = 0;
	// �S���N���}
	if( aList.isEmpty() )
		return;
	// 1. ���ܨín�D��J K ��(�n�����ƶq)
	cout << endl << "Enter the value of K in [1, " << aDeap.size() - 1 << "]: ";
	cin >> command;

	// 2. ��J�Ȧp�G�W�X�d�ҴN�Q�����}
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
	// 3. ��X���̤j��
	for( i = 0 ; i < command ; ++i )
	{
		// 3.1 pop �@�ӳ̤j�ȥX��
		const ScrollType * pct = aDeap.popMax();
		// 3.2 �p�G��ƬO�Ū��A�N����
		if( pct == NULL )continue;
		// 3.3 �L�X���
		const ScrollType& data = *pct;

		sprintf( ch , "Top%4d: [%d] %s%s, %s, %s, %d\n" , ( i + 1 ) , data.index , data.schoolName.c_str() ,
				data.departmentName.c_str() , data.dayFurtherStudy.c_str() , data.level.c_str() ,
				data.numberOfStudents );
		cout << ch;
	}
}

// ���եΪ� 4
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
		case 2: // 1 �U���J deap ���O
			runMenu2( deap , aList );
			break;
		case 3: // 2. ��XDeap �eK�ճ̤j���ƭȡA
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

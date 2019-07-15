    #include<iostream>
    using namespace std;
     
    class L
    {
    private:
    	int flag=-1;
        int count = 0;
        int elem[10000] = { 0 };
    public:
        L() {};
        ~L() {};
     
        void create_list()
        {
            for (int i = 0;; i++)
            {
                cin >> elem[i];
                count++;
                if (elem[i] == 0)
                    break;
            }
            count -= 1;
        }
     
        void sort()
        {
            int temp;
            for (int i = 0; i < count - 1; i++)
            {
                for (int j = 0; j < count - 1 - i; j++)
                {
                    if (elem[j] > elem[j + 1])
                    {
                        temp = elem[j];
                        elem[j] = elem[j + 1];
                        elem[j + 1] = temp;
                    }
                }
            }
        }//升序排列
     
        void insert_elem()
        {
            int in, i;
            cin >> in;
     
            if (in >= elem[count - 1])
            {
                cout << count + 1 << endl;
                elem[count] = in;
            }
     
            else if (in <= elem[0])
            {
                cout << 1 << endl;
                for (int q = count - 1; q >= 0; q--)
                {
                    elem[q + 1] = elem[q];
                }
                elem[0]=in;
            }
     
            else
            {
                for (i = 0; i < count; i++)
                {
                    if (in > elem[i] && in <= elem[i + 1])
                    {
                        cout << i + 2 << endl;
                        for (int j = count - 1; j > i; j--)
                        {
                            elem[j + 1] = elem[j];
                        }
                        elem[i + 1] = in;
                        break;
                    }
                }
            }
        }
     
        void delete_elem()
        {
            int de, i;
            cin >> de;
     
            for (i = 0; i < count + 1; i++)
            {
                if (elem[i] == de)
                {
                    flag = i+1;
                    elem[i] = 0;
                    break;
                }
            }
            cout << flag << endl;
     
            if (flag != -1)
            {
                if (i == count)
                    elem[count] = 0;
                else
                {
                    for (int j = i; j < count; j++)
                    {
                        elem[j] = elem[j + 1];
                    }
                    elem[count] = 0;
                }
            }
        }
     
        void output()
        {
        	if (flag!=-1)
        	{
                for (int i = 0; i<count; i++)
                {
                    cout << elem[i] << " ";
                }
                cout << endl;
            }
            else 
            {
            	for (int i = 0; i<count+1; i++)
                {
                    cout << elem[i] << " ";
                }
                cout << endl;
            }
        }
    }List;
     
    int main()
    {
        List.create_list();
        List.sort();
        List.insert_elem();
        List.delete_elem();
        List.output();
        return 0;
    }
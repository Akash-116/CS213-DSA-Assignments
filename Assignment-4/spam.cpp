// t < s now.....
// 


		for(int idx = p; idx < t; idx++)
		{
			count++;
			cout << w_arr[idx] << " " << v_arr[idx] << endl;
		}

		if(q==0)
		{
			cout << w_arr[p-1] << " " << v_arr[t] << endl; count++;

			for(int idx = t; idx < s-1 ; idx++)
			{
				cout << v_arr[idx] << " " << v_arr[idx+1] << endl; count++;
			}

			cout << v_arr[s-1] << " " << v_arr[0] << endl; count++;
		}


		else
		{
			cout << w_arr[p-1] << " " << v_arr[t] << endl; count++;

			for(int idx = t; idx < s-1; idx++ )
			{
				cout << v_arr[idx] << " " << v_arr[idx+1] << endl; count++;
			}

			cout << v_arr[s-1] << " " << x_arr[0] << endl; count++;

			for(int idx = 0; idx < q-1; idx++)
			{
				cout << x_arr[idx] << " " << x_arr[idx+1] << endl; count++;
			}

			cout << x_arr[q-1] << " " << v_arr[0] << endl; count ++;

		}
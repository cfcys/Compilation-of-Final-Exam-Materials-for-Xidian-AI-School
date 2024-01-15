//朴素的模式匹配的算法

int Index(String S,String T,int pos)
{	
	int i = pos;  //i用于主串S中当前位置的下标
	int j = 1;
	while(i <= S[0] && j <= T[0])   //当i小于S的长度并且j小于T的长度的时候执行该循环
	{
		if(S[i] == T[j]){
			++j;
			++i;
		}
		else{
			i = i - j + 2;//这样使得i退回到上次匹配位置的下一位
			j = 1; 		  //j退回到子串T的首位
		}
	}
	if(j > T[0]){
		return i-T[0];
	}else{
		return 0;
	}
}
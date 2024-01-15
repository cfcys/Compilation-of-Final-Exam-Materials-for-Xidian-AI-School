	
	栈的顺序栈
		入栈 Push
		出栈 Pop  
			取值(malloc) + 修改栈顶的指针
			通过引用带回 
				(SeqStack *S,datatype &x) 	！&可以修改实参！
				就不用malloc了
	定义
	
	
	
	链栈（有无头节点） LinkStack
		入栈
			带有头节点
				PushS(){
				
				}
	
		出栈
			带有头节点
				有引用 
					使得函数()中的参数可以真正的被修改
					这样就不需要 函数定义成返回的类型   并且函数中有malloc这个结构
					
					
	队列(先到先出)（FIFO）
		rear队尾
		front队首
		（1）建立二叉树的时候使用队列
		（2）递归 --> 非递归  使用栈
				顺序队列
					int front rear
					front 默认指向队头的前一个位置
					入队  sq->rear++; sq->data[sq->rear] = x;
					出队  x =    ; front++;
					front == rear   相等 空队
					
					问题：
					入队和出队操作会存在未使用的储存单元，假上溢！
					      --->  顺序队列 -》 （环状队列）
					so 顺序队列 默认就是 环状队列
						入队
						sq -> rear = (sq->rear + 1) % maxsize
						出队
						sq -> front = (sq->front + 1) % maxsize
					循环队列空和满的情况无法区分：
						1  设置空/满标志
						2  len == 0  || len == maxsize - 1
						333  常用 
							牺牲一个存储的单元，队列的最大长度为maxsize-1
							该牺牲单元随着不断地入队和出队是在不断地游动的
							队满的条件： (sq->rear + 1) % maxsize == sq->front
							队空的条件： ()
					
					初始化   重点看一下使用引用带回的形式
							
	
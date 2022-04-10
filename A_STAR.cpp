

#include <stdio.h>
#include <stdlib.h>
#include <math.h>   //Ϊ��ʹ��sqrt()����

#define END_X 0
#define END_Y 4
#define START_X 3
#define START_Y 1
#define MAP_LENTH 5
#define MAP_WIDTH 5

#define ERROR -1

//---------------------------------------------------------------------------//

//����open list��close list(�����нڵ㣬�ڵ㻹���Լ�������)
//�������������Ǹ��ṹ�壬��������Ҳ���ǽڵ������F��G��H��������ȵ�

typedef struct Open_list Open_list, * pOpen_list;
typedef struct Node
{
    //���ڵ�
    pOpen_list  pFather;
    float G;
    float H;
    //Fֵ
    float F;
    //x,y����
    int x;
    int y;
}Node, * pNode;

typedef struct Open_list
{
    struct Open_list * next;
    struct Node node; 
}Open_list, * pOpen_list;

//---------------------------------------------------------------------------//
//��غ���
float my_abs(int x);
//���뺯��������������(x1,y1)�ͣ�x2��y2����
float my_distance(int x1, int y1, int x2, int y2);
//�������
void list_add_tail(pOpen_list my_list, pOpen_list add_node);
//��������,������tmpY��tmpYƥ��Ľڵ�ָ��
pOpen_list list_browse(pOpen_list my_list, int tmpX, int tmpY);
//�ж��������ǲ�����ĳ���ڵ㣨ͨ��������ȷ�������еĻ�����0��û�з���1
int judge_node_exist(pOpen_list mylist, int x, int y);
//ɾ��������ĳ���ڵ㣬ͨ������ɾ��,���ҷ������ɾ���Ľڵ�ָ�룬������뵽close list
pOpen_list list_delete_point(pOpen_list my_list, int tmpX, int tmpY);
//�ҵ���������С��fֵ�ĺ���,��������������Сf�Ľڵ�
pOpen_list find_min_f(pOpen_list my_list);
//��ӡopen list�еĸ����ڵ������Լ�Fֵ
void msg_open_list(pOpen_list my_list);
//��ӡ���ڵ����꺯��
void printf_father_node(pOpen_list my_list);

//---------------------------------------------------------------------------//


int main(int argc, char ** argv)
{
    //************************************************************************//
    //1��������ͼ
    


	//�ϰ���Ϊ1��startΪ2��endΪ3
    int map[MAP_LENTH][MAP_WIDTH] = 
    {
        {0,0,0,0,3},
        {0,0,0,1,1},
        {1,1,1,0,0},
        {0,2,0,1,0},
        {0,0,0,0,0}
    };

    //************************************************************************//
    
    //2.��������open list

    //����һ��ָ��pOָ��open list��һ��ָ��pCָ��close list��ע������open list��pOָ����ǿ��ڴ�
    pOpen_list pO = (pOpen_list)malloc(sizeof(Open_list));
    pO->next = NULL;
    //pO = NULL;  ǧ�򲻿��ԣ�NULL�����Է��ʵģ�����pO��ֵ
    pOpen_list pC = (pOpen_list)malloc(sizeof(Open_list));
    pC->next = NULL;

    //������ʼ�ڵ㲢��ʼ��������һ��Ŀ��ڵ�
    pOpen_list start = (pOpen_list)malloc(sizeof(Open_list));
    start->next = NULL;
	pOpen_list end = (pOpen_list)malloc(sizeof(Open_list));
	end->next = NULL;
    
    start->node.pFather = NULL;
    start->node.x = START_X;
    start->node.y = START_Y;
    start->node.G = 0;
    start->node.H = (my_abs(END_X - START_X) + my_abs(END_Y - START_Y));
    start->node.F = start->node.G + start->node.H;

	end->node.pFather = NULL;
    end->node.x = END_X;
    end->node.y = END_Y;

    //��ʼ�ڵ���뵽open list
    list_add_tail(pO, start);

 
    int i,j;    //����������

    //************************************************************************//
	int cir = 1;
    while(cir)
    {
        //printf("-------------------begin while--------------\n");
		//Ѱ����С��Fֵ�ڵ㣬��ΪpCurrent����һ��ѭ��Ҳ������㣩
        //pOpen_list pCurrent = (pOpen_list)malloc(sizeof(Open_list));
		msg_open_list(pO);	//����open list���еĽڵ�
		pOpen_list pCurrent = find_min_f(pO);  //�п����Ҳ���
		
        //*********************************************************************//

		//�ѵ�ǰ���open list���Ƴ���ͨ�����꣩�����뵽close list����Ϊp
		pOpen_list p = list_delete_point(pO, pCurrent->node.x, pCurrent->node.y);
		list_add_tail(pC, p);
		printf("core is (%d, %d)\n", p->node.x, p->node.y);
		
		printf("now ,the open list is as follow\n");
		msg_open_list(pO);
		//printf("------------------------begin for  for------------------\n");

        //*********************************************************************//

        //��Ҫ�����ǲ����ϰ����û����close list����open list,�����ǲ��Ǳ߽�
        //���Ӧ���Ǳ�����ǰ�ڵ�(p->node.x, p->node.y)�����ܣ����Ҷ�����open list
        for(i = -1; i < 2; i++)
        {
            for(j = -1; j < 2; j++)
            {
				if((p->node.x + i < 0) || (p->node.x + i > 4) || (p->node.y + j < 0) || (p->node.y + j > 4))	//�����߽��ˣ��������ѭ��
					continue;
				
				if(judge_node_exist(pO, (p->node.x + i), (p->node.y + j)))    //����open list����Ľڵ�
                {
                    if(1 == map[p->node.x + i][p->node.y + j])   //���ɵ���
                    {
						//printf("(%d, %d) is not-reach\n", (p->node.x + i), (p->node.y + j));
						continue;
					}						
                    else if(!(judge_node_exist(pC, (p->node.x + i), (p->node.y + j))))   //��close list��
                    {
						//printf("(%d, %d) is close list\n", (p->node.x + i), (p->node.y + j));
						continue;
					}   
                    else if(((p->node.x + i)==END_X) && ((p->node.y+j)==END_Y))  //��Ŀ��ڵ㣬��ʼ��
                    {
                        printf("���ҵ�\n");
						end->node.pFather = p;		//��ǰ�ڵ���Ϊend �ĸ��ڵ�
						cir = 0;	//����ѭ����־��ע����������for
                        break;
                    }
                    else    //����open list�е���ͨ�ڵ㣬�����ȥ��ʼ������ø��ڵ�
                    {
                        //printf("(%d, %d) is normal node\n", (p->node.x + i), (p->node.y + j));
						
						pOpen_list pTmp = (pOpen_list)malloc(sizeof(Open_list));
						pTmp->next =NULL;

                        pTmp->node.pFather = p;  //���ڵ�Ϊ��ǰ�ڵ�
                        //�ڵ�����
                        pTmp->node.x = p->node.x + i;
                        pTmp->node.y = p->node.y + j;
                        //�ڵ�G.H.Fֵ       Gֵ��ô���(�ҵ����ڵ�����ڽڵ��������)
                        pTmp->node.G = my_distance(pTmp->node.x, pTmp->node.y, START_X, START_Y);   //��ʼ�ڵ㵽��ʵ�ʾ���
                        pTmp->node.H = (my_abs(END_X - pTmp->node.x) + my_abs(END_Y - pTmp->node.y));
                        pTmp->node.F = pTmp->node.G + pTmp->node.H;

                        //���뵽open list
                        list_add_tail(pO, pTmp);
						msg_open_list(pO);
                    }				
                }
                else    //��open list����
                {
					//printf("---------------------in open list-------------------\n");
					//printf("(%d, %d) in open list\n", (p->node.x + i), (p->node.y + j));
					//���ȸ��������ҵ�����ָ��
                    //pOpen_list pTmp = (pOpen_list)malloc(sizeof(Open_list));
					//pOpen_list pTmp = (pOpen_list)malloc(sizeof(Open_list));
                    pOpen_list pTmp = list_browse(pO, (p->node.x + i), (p->node.y + j));
                    //�����������Gֵ(һ����ԭ����Gֵ��һ����ͨ����ǰ�ڵ㵽��Gֵ)
					//�����ú��Ľڵ��Gֵ���ϵ�ǰ�ڵ㵽���Ľڵ��ֵ
                    float currentG = p->node.G + my_distance(pTmp->node.x, pTmp->node.y, p->node.x, p->node.y);
                    float pastG = pTmp->node.G;
                    
					//printf("currentG: %f      pastG: %f\n", currentG, pastG);
                    if(currentG < pastG)    //��ǰ����
                    {
                        pTmp->node.pFather = p; //�������ڵ�
                        //ע�⣬����Fֵ��Gֵһ��
                        pTmp->node.G = currentG;
                        pTmp->node.F = pTmp->node.G + pTmp->node.H;
                    }   
                }
            }
			if(cir == 0)	//��������forѭ��
				break;
        } 
    }
    
	
	//���ﲻ���ã�������msg_open_list��������Ǵ�ӡ���е�����
	// msg_open_list(end->node.pFather);		//0,3
	
	// msg_open_list((end->node.pFather)->node.pFather);  //1,2
	// msg_open_list(end->node.pFather->node.pFather->node.pFather);
	printf_father_node(end);



    
    return 0;
}
//�ҵ��ˣ�Ȼ����������ѭ��

//β����������
void list_add_tail(pOpen_list my_list, pOpen_list add_node)
{
	pOpen_list tmp = my_list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = add_node;
	add_node->next = NULL;
}

//ɾ��������ĳ���ڵ㣬ͨ������ɾ��,���ҷ������ɾ���Ľڵ�ָ�룬����free
pOpen_list list_delete_point(pOpen_list my_list, int x, int y)
{

    while (my_list->next != NULL)
	{
        if((my_list->next->node.x == x) && (my_list->next->node.y == y))  //�ҵ�ɾ���ڵ�
        {
            pOpen_list tmp = my_list->next;
			//����ڵ㲻�����һ���ڵ�
			if(my_list->next->next != NULL)
			{
				my_list->next = my_list->next->next;

				tmp->next = NULL;
			}
			else //���һ���ڵ�
			{
				my_list->next = NULL;

				tmp->next = NULL;
			}
            return tmp;
        }
        my_list = my_list->next;  
	}

	return NULL;
}

//��������,������p->node.y��p->node.yƥ��Ľڵ�ָ��
pOpen_list list_browse(pOpen_list my_list, int x, int y)
{

    while (my_list->next != NULL)
	{
		if((my_list->next->node.x == x) && (my_list->next->node.y == y))
        {
            return my_list->next;
        }
        my_list = my_list->next;  
	}

	return NULL;
}

//�ж��������ǲ�����ĳ���ڵ㣨ͨ��������ȷ�������еĻ�����0��û�з���1
int judge_node_exist(pOpen_list mylist, int x, int y)
{
    while(mylist->next != NULL)
    {
        if((mylist->next->node.x == x) && (mylist->next->node.y == y))	//��open list
        {
            return 0;
        }
        mylist = mylist->next;
    }

	return 1;
}

//�ҵ���������С��fֵ�ĺ���,��������������Сf�Ľڵ�
pOpen_list find_min_f(pOpen_list my_list)
{
    //����һ����ʱ����tmpfΪ�ڶ����ڵ��Fֵ����������ȥ
    int tmpf = my_list->next->node.F;
    pOpen_list tmpp = my_list->next;

    while(my_list->next != NULL)
    {
        
        if(tmpf > my_list->next->node.F)
        {
            tmpf = my_list->next->node.F;
            tmpp = my_list->next;       //��һ��ѭ���Ϳ����ҵ���ע�⣡����
        }
        my_list = my_list->next;
    }

    //�ҵ���Fֵ��Ϊtmpf����ô�ҵ���Ӧ�Ľڵ㣬Ϊʲô�����Ŷ���һ����ʱ�ڵ���
    return tmpp;
}

//��ӡopen list�еĸ����ڵ������Լ�Fֵ
void msg_open_list(pOpen_list my_list)
{
    while(my_list->next != NULL)
    {
        int x = my_list->next->node.x;
        int y = my_list->next->node.y;

        float f = my_list->next->node.F;
        printf("is (%d, %d).   F = %f\n", x, y, f);

        my_list = my_list->next;
    }
}

//��ӡ���ڵ����꺯��
void printf_father_node(pOpen_list my_list)
{
	while(my_list->node.pFather != NULL)
	{
		printf("is(%d, %d)\n", my_list->node.pFather->node.x, my_list->node.pFather->node.y);

		my_list = my_list->node.pFather;
	}

	printf("track end\n");
}

//����ֵ�������ҵģ�
float my_abs(int x)
{
    if(x < 0)
    {
        return (float)(-x);
    }
    else
    {
       return (float)(x);
    }
}

//���뺯��������������(x1,y1)�ͣ�x2��y2����
float my_distance(int x1, int y1, int x2, int y2)
{
    return sqrt(  (my_abs(x1-x2)*my_abs(x1-x2)) + (my_abs(y1-y2)*my_abs(y1-y2)) );
}



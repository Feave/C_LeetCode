//
//  main.c
//  LearningC
//
//  Created by qitmac000018 on 2017/5/9.
//  Copyright © 2017年 qitmac000018. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX(a,b) ((a>b)?a:b)
#define STACKMAX 100

#pragma mark 链表
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* initListNode(int *nums, int size){
    struct ListNode* headNode = malloc(sizeof(struct ListNode));
    struct ListNode* tailNode = malloc(sizeof(struct ListNode));
    headNode->val = nums[0];
    headNode->next = NULL;
    tailNode = headNode;
    if (size < 2) {
        return headNode;
    }
    for (int i  = 1; i < size; i++) {
        struct ListNode* newNode = malloc(sizeof(struct ListNode));
        newNode->val = nums[i];
        newNode->next = NULL;
        tailNode->next = newNode;
        tailNode = newNode;
    }
    return headNode;
}

void printListNode(struct ListNode *node)
{
    if(NULL == node)   //链表为空
    {
        printf("null node\n");
    }
    else
    {
        while(NULL != node)
        {
            printf("%d ",node->val);
            node = node->next;
        }
        printf("\n");
    }
}

#pragma mark 树
struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* initTree(int *elements,int size){
    int lor = 0,index = 1;
    struct TreeNode *node[size];
    if (size < 1) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        node[i] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        if (elements[i] == 0) {
            node[i] = NULL;
        } else {
            node[i]->val = elements[i];
            node[i]->right = NULL;
            node[i]->left = NULL;
        }
    }
    
    for (int j = 0; index<size; j++) {
        if (node[j] != NULL) {
            if (lor) {
                node[j]->right = node[index];
                index++;
                lor = 0;
            } else {
                node[j]->left = node[index];
                index++;
                lor = 1;
                j--;
            }
        }
    }
    return node[0];
}
#pragma mark 队列
struct queue{
    struct TreeNode *data[STACKMAX];
    int front;
    int rear;
};

void enter(struct queue *q,struct TreeNode *t){
    if (q->rear == STACKMAX) {
        printf("the queue is full!\n");
    } else {
        q->data[q->rear] = t;
        q->rear++;
    }
}

struct TreeNode* delete(struct queue *q){
    if (q->front == q->rear) {
        return NULL;
    } else{
        q->front++;
        return q->data[q->front-1];
    }
}

#pragma mark 栈
struct stack{
    struct TreeNode *data[STACKMAX];
    int top;
};

void push(struct stack *s,struct TreeNode *t){
    if (s->top > STACKMAX) {
        printf("stack overflow!\n");
    } else {
        s->data[s->top] = t;
        s->top++;
    }
}

struct TreeNode* pop(struct stack* s){
    if (s->top == 0) {
        return NULL;
    } else {
        s->top--;
        return s->data[s->top];
    }
}

struct TreeNode* getTop(struct stack *s){
    if (s->top < 0) {
        return NULL;
    } else {
        return s->data[s->top-1];
    }
}

void printTreeNode(struct TreeNode *node){
    struct queue *q = malloc(sizeof(struct queue));
    q->front = q->rear = 0;
    if (node != NULL) {
        enter(q, node);
        while (q->front != q->rear) {
            node = delete(q);
            printf("%d  ",node->val);
            if (node->left) {
                enter(q, node->left);
            }
            if (node->right) {
                enter(q, node->right);
            }
        }
        printf("\n");
    } else {
        return;
    }
}

#pragma mark 排序算法

//排序算法
void bucketSort(int *nums,int numsSzie,int maxNum){
    int bucket[maxNum];
    memset(bucket, 0, maxNum);
    for (int i = 0; i < numsSzie; i++) {
        if (nums[i] >= 0) {
            bucket[nums[i]]++;
        }
    }
    
    for (int j = 0,count = 0; count < numsSzie; ) {
        if (bucket[j] > 0) {
            nums[count] = j;
            count++;
            if (--bucket[j] == 0) {
                j++;
            }
        } else {
            j++;
        }
    }
}

#pragma mark LeetCode

//LeetCode 1. Two Sum
int* twoSum(int *nums,int numsSize,int target){
    int *returnSize = malloc(sizeof(int)*2);
    returnSize[0]=returnSize[1]=0;
    int maxPosiNum=0;
    int minNegaNum=0;
    
    for(int i=0;i<numsSize;i++){
        if(nums[i]>maxPosiNum)
            maxPosiNum=nums[i];
        else if(nums[i]<minNegaNum)
            minNegaNum=nums[i];
    }
    
    int PosiArr[maxPosiNum+1];
    int PosiArr1[maxPosiNum+1]; //if the number appears more than once, then put it in this array
    int NegaArr[-minNegaNum+1];
    int NegaArr1[-minNegaNum+1];
    memset(PosiArr,0,sizeof(int)*(maxPosiNum+1));
    memset(PosiArr1,0,sizeof(int)*(maxPosiNum+1));
    memset(NegaArr,0,sizeof(int)*(-minNegaNum+1));
    memset(NegaArr1,0,sizeof(int)*(-minNegaNum+1));
    for(int j=0;j<numsSize;j++){
        if (nums[j]>=0) {
            (PosiArr[nums[j]]>0)?(PosiArr1[nums[j]]=j+1):(PosiArr[nums[j]]=j+1);
        }
        else{
            (NegaArr[-nums[j]]>0)?(NegaArr1[-nums[j]]=j+1):(NegaArr[-nums[j]]=j+1);
        }
    }
    int lookforNum=0;
    for(int k=0;k<numsSize;k++){
        lookforNum=target-nums[k];
        if(lookforNum>=minNegaNum&&lookforNum<=maxPosiNum){
            if(lookforNum>=0&&PosiArr[lookforNum]>0&&lookforNum!=nums[k]){
                returnSize[0]=(k+1<PosiArr[lookforNum])?k+1:PosiArr[lookforNum];
                returnSize[1]=(k+1>PosiArr[lookforNum])?k+1:PosiArr[lookforNum];
                break;
            }
            else if(lookforNum<0&&NegaArr[-lookforNum]>0&&lookforNum!=nums[k]){
                returnSize[0]=(k+1<NegaArr[-lookforNum])?k+1:NegaArr[-lookforNum];
                returnSize[1]=(k+1>NegaArr[-lookforNum])?k+1:NegaArr[-lookforNum];
                break;
            }
            else if(lookforNum>=0&&PosiArr1[lookforNum]>0&&lookforNum==nums[k]){
                returnSize[0]=PosiArr[lookforNum];
                returnSize[1]=PosiArr1[lookforNum];
                break;
            }
            else if(lookforNum<0&&NegaArr1[-lookforNum]>0&&lookforNum==nums[k]){
                returnSize[0]=NegaArr[-lookforNum];
                returnSize[1]=NegaArr1[-lookforNum];
                break;
            }
        }
    }
    printf("index:%d,%d\n",returnSize[0],returnSize[1]);
    return returnSize;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carryFlag = 0;
    struct ListNode* resNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* pNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    resNode->val = l1->val + l2->val;
    if (resNode->val > 9) {
        carryFlag = 1;
        resNode->val -= 10;
    }
    resNode->next = NULL;
    pNode = resNode;
    while(1){
        if (l1->next != NULL || l2->next != NULL) {
            struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
            newNode->val = carryFlag;
            if (l1->next != NULL) {
                newNode->val += l1->next->val;
                l1->val = l1->next->val;
                l1->next = l1->next->next;
            } else {
                pNode->next = l2->next;
            }
            if (l2->next != NULL) {
                newNode->val += l2->next->val;
                l2->val = l2->next->val;
                l2->next = l2->next->next;
            } else {
                pNode->next = l1->next;
            }
            if (newNode->val > 9) {
                carryFlag = 1;
                newNode->val = newNode->val - 10;
            } else {
                carryFlag = 0;
            }
            newNode->next = NULL;
            pNode->next = newNode;
            pNode = newNode;
        } else {
            struct ListNode* lastNode = (struct ListNode*)malloc(sizeof(struct ListNode));
            if (carryFlag == 1) {
                lastNode->val = 1;
                lastNode->next = NULL;
                pNode->next = lastNode;
            }
            break;
        }
    }
    return resNode;
}

//LeetCode 120 Triangle
int minimumTotal(int** triangle, int triangleRowSize, int *triangleColSizes) {
    int *bPath = triangle[triangleRowSize - 1];
    for (int i = 1;i < triangleRowSize;i++){
        int *tPath = triangle[triangleRowSize - i -1];
        for(int j = 0;j < triangleColSizes[triangleRowSize - i];j++){
            bPath[j] = (bPath[j] > bPath[j+1]?bPath[j+1]:bPath[j]) + tPath[j];
        }
    }
    return bPath[0];
}

int robI(struct TreeNode *root){
    if (root == NULL){
        return 0;
    }
    int val = 0;

    if (root->left != NULL) {
        val += robI(root->left->left) + robI(root->left->right);
    }
    if (root->right != NULL) {
        val += robI(root->right->left) + robI(root->right->right);
    }
    
    
    return MAX(root->val + val,robI(root->left) + robI(root->right));
}

int* robSub(struct TreeNode *root){
    int *res = malloc(sizeof(int)*2);
    res[0] = 0;
    res[1] = 0;
    if (root == NULL) {
        return res;
    }
    
    int *left = robSub(root->left);
    int *right = robSub(root->right);
    
    res[0] = MAX(left[0], left[1]) + MAX(right[0], right[1]);
    res[1] = root->val + left[0] +right[0];
    
    return res;
}

int robIII(struct TreeNode *root){
    int *res = robSub(root);
    return MAX(res[0], res[1]);
}

int hammingDistance(int x,int y){
    int dis =  x^y;
    /**快速法 n &= (n – 1) 清除最右边的1
     **/
     unsigned int c;
     for (c = 0; dis; c++) {
     dis &= (dis-1);
     }
     return c;
     
    /** 静态表-8bit
    unsigned int table[256] =
    {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    };
    
    return table[dis &0xff] +
    table[(dis >>8) &0xff] +
    table[(dis >>16) &0xff] +
    table[(dis >>24) &0xff] ;
     **/
    
    /** 平行算法
    dis = (dis &0x55555555) + ((dis >>1) &0x55555555) ;
    dis = (dis &0x33333333) + ((dis >>2) &0x33333333) ;
    dis = (dis &0x0f0f0f0f) + ((dis >>4) &0x0f0f0f0f) ;
    dis = (dis &0x00ff00ff) + ((dis >>8) &0x00ff00ff) ;
    dis = (dis &0x0000ffff) + ((dis >>16) &0x0000ffff) ;
    return dis ;
     **/
}

struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2) {
    /** 递归解决
     **/
    if (t1 == NULL) {
        return t2;
    }
    if (t2 == NULL) {
        return t1;
    }
    t1->val += t2->val;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);
    
    /** 栈
    if (t1 == NULL) {
        return t2;
    }
    struct stack *s = malloc(sizeof(struct stack));
    s->top = 0;
    struct TreeNode *pairT = malloc(sizeof(struct TreeNode));
    pairT->left = t1;
    pairT->right = t2;
    push(s, pairT);
    while (s->top != 0) {
        struct TreeNode *t = pop(s);
        if (t->left == NULL || t->right == NULL) {
            continue;
        }
        t->left->val += t->right->val;
        
        if (t->left->left == NULL) {
            t->left->left = t->right->left;
        } else {
            struct TreeNode *pairT = malloc(sizeof(struct TreeNode));
            pairT->left = t->left->left;
            pairT->right = t->right->left;
            push(s, pairT);
        }
        
        if (t->left->right == NULL) {
            t->left->right = t->right->right;
        } else {
            struct TreeNode *pairT = malloc(sizeof(struct TreeNode));
            pairT->left = t->left->right;
            pairT->right = t->right->right;
            push(s, pairT);
        }
    }
     **/
    return t1;
}

int arrayPairSum(int* nums,int numsSize){
    int ret = 0;
    int hashtable[20001] = {0};
    for (int i = 0; i < numsSize; i++) {
        hashtable[nums[i] + 10000]++;
    }
    for (int i = 0,count = 0; count < numsSize; ) {
        if (hashtable[i] > 0) {
            if (count%2 == 0) {
                ret += i - 10000;
            }
            count++;
            if (--hashtable[i] == 0) {
                i++;
            }
        } else {
            i++;
        }
    }
    return ret;
}

int judgeoneline(char *str)
{
    int i;
    int table[26] = {0,-1,-1,0,1,0,0,0,1,0,0,0,-1,-1,1,1,1,1,0,1,1,-1,1,-1,1,-1};
    for(i=0;*(str+i+1)!='\0';i++){
        if(table[(tolower(str[0])) - 'a']!=table[tolower(*(str+i+1)) - 'a'])	break;
    }
    if (str[i+1] != '\0')
        return(0);
    else
        return(1);
}
char** findWords(char** words, int wordsSize, int* returnSize)
{
    *returnSize = 0;
    int j;
    char **str = (char **)malloc(sizeof(char *)*wordsSize);
    for(j=0;j<wordsSize;j++){
        if(judgeoneline(*(words+j))==1){
            *(str+*returnSize) = *(words+j);
            (*returnSize)++;
        }	
    }
    return(str);
}

void reverse(int b,int e,char *s){
    while (b < e) {
        s[b] = s[b]^s[e];
        s[e] = s[b]^s[e];
        s[b] = s[b]^s[e];
        b++;
        e--;
    }
}

char* reverseWords(char* s) {
    int i, s_len = (int)strlen(s), index = 0;
    
    for(i = 0; i <= s_len; i++) {
        if((s[i] == ' ') || (s[i] == '\0')){
            reverse(index, i - 1, s);
            index = i + 1;
        }
    }
    return s;
}

char* predictPartyVictory(char* senate) {
    int s_length = (int)strlen(senate),r=0,d=0,p=0;
    int *rIndex = malloc(sizeof(int)*s_length);
    int *dIndex = malloc(sizeof(int)*s_length);
    for (int i = 0;i<s_length;i++){
        if(senate[i] == 'R'){
            rIndex[r] = i;
            r++;
        }else{
            dIndex[d] = i;
            d++;
        }
    }
    int br = 0,bd= 0;
    while(senate[rIndex[r-1]] != 'B' && senate[dIndex[d-1]] != 'B'){
        p = p%s_length;
        if(senate[p] == 'R'){
            senate[dIndex[bd]] = 'B';
            bd++;
        } else if(senate[p] == 'D'){
            senate[rIndex[br]] = 'B';
            br++;
        }
        p++;
    }
    if (senate[rIndex[r-1]] == 'B'){
        return "Dire";
    } else {
        return "Radiant";
    }
}

int main(int argc, const char * argv[]) {
    int num = 649;
    //scanf("%d",&num);
    switch (num) {
        case 1:{
            /**
             1. Two Sum
             **/
            int array[] = {3,1,4,5,7,3,9};
            int res = 14;
            twoSum(array, sizeof(array)/sizeof(int), res);
        }
            break;
        case 2:{
            /**
             2 Add Two Numbers
             **/
            int nums1[] = {4,3,4,3,5,5,2,3,1,2};
            int nums2[] = {6,7,2,4,0,9,7,8,9,1};
            struct ListNode* l1 = initListNode(nums1, sizeof(nums1)/sizeof(int));
            struct ListNode* l2 = initListNode(nums2, sizeof(nums2)/sizeof(int));
            struct ListNode* resNode = addTwoNumbers(l1, l2);
            printListNode(resNode);
        }
            break;
        case 120:{
            /**
             LeetCode 120. Triangle
             **/
            int triangle[4][4] = {{2},{3,4},{6,5,7},{4,10,8,3}};
            int *p[4] = {triangle[0],triangle[1],triangle[2],triangle[3]};
            int **dp = &p[0];
            int triangleColSizes[4] = {1,2,3,4};
            int sum = minimumTotal(dp, 4,triangleColSizes);
            printf("%d\n",sum);
        }
            break;
        case 337:{
            /**
             LeetCode 337. House Robber III
             **/
            int elements[] = {3,2,3,1,3,0,10,7};
            struct TreeNode *node = initTree(elements, sizeof(elements)/sizeof(int));
            printf("robI:%d\n",robI(node));
            printf("robIII:%d\n",robIII(node));
        }
            break;
        case 461:{
            /**
             461. Hamming Distance
             **/
            printf("hammingDistance:%d\n", hammingDistance(1, 4));
        }
            break;
        case 476:{
            /**
             476. Number Complement
             **/
            int num = 5;
            int index = 0;
            int r = num;
            while(r){
                r = r>>1;
                index++;
            }
            printf("Number Complement:%d\n",~((0xffffffff<<index)+num));
        }
            break;
        case 500:{
            /**
             500. Keyboard Row
             **/
            char *words[] = {"Hello","Alaska","Dad","Peace"};
            int returnSize = 0;
            char **findwords = findWords(words, sizeof(words)/sizeof(char*), &returnSize);
            for (int i = 0; i < returnSize; i++) {
                printf("%s ",findwords[i]);
            }
            printf("\n");
        }
            break;
        case 557:{
            /**
             557. Reverse Words in a String III
             **/
            char s[] = "Let's take LeetCode contest";
            printf("%s\n",reverseWords(s));
        }
            break;
        case 561:{
            /**
             561. Array Partition I
             **/
            int nums[] = {1,4,3,2,394,2,457,4};
            printf("arrayPairSum:%d\n",arrayPairSum(nums,sizeof(nums)/sizeof(int)));
        }
            break;
        case 617:{
            /** 
             Merge Two Binary Trees
             **/
            int nums1[] = {1,3,2,5};
            int nums2[] = {2,1,3,0,4,0,7};
            struct TreeNode* t1 = initTree(nums1, sizeof(nums1)/sizeof(int));
            struct TreeNode* t2 = initTree(nums2, sizeof(nums2)/sizeof(int));
            struct TreeNode* mergeT = mergeTrees(t1, t2);
            printTreeNode(mergeT);
        }
            break;
        case 649:{
            //649. Dota2 Senate
            char senate[] = "R";
            printf("Dota2 Senate:%s\n",predictPartyVictory(senate));
        }
        default:
            break;
    }
    
    return 0;
}

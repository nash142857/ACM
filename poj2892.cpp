/*treap应用 每个点赋一个rand()优先值 达到平衡树*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int oo = 10000000;
struct treap{
	int l, r, key, fix;
	treap(int a = 0, int b = 0, int c = 0, int d = 0){/*初始化*/
		l = a;
		r = b;
		key = c;
		fix = d;
	}
}tree[101000];
int n, m, st[51000], cnt, tot, root;
char s[2];
void rol(int &p){/*两个旋转*/
	int c = tree[p].r;
	tree[p].r = tree[c].l;
	tree[c].l = p;
	p = c;
}
void ror(int &p){
	int c = tree[p].l;
	tree[p].l = tree[c].r;
	tree[c].r = p;
	p = c;
}
void insert(int & p, int k){
	if(p == 0){
		cnt++;/*新增节点*/
		tree[cnt] = treap(0, 0, k, rand());/*通过引用返回*/
		p = cnt;
		return;
	}
	if(tree[p].key < k){
		insert(tree[p].r, k);
		if(tree[tree[p].r].fix > tree[p].fix)
			rol(p);/*插入时根据fix 判断是否需要旋转*/
	}
	else{
		insert(tree[p].l, k);
		if(tree[tree[p].l].fix > tree[p].fix)
			ror(p);
	}
}
void del(int &p, int k){/*删除只需要找到节点 然后旋至叶节点即可*/
	if(tree[p].key == k){
		if(tree[p].l && tree[p].r){
			if(tree[tree[p].l].fix > tree[tree[p].r].fix){
				ror(p);
				del(tree[p].r, k);
				return;
			}
			else{
				rol(p);
				del(tree[p].l, k);
				return;
			}
		}
		else{
			if(tree[p].l)
			 p = tree[p].l;
			 else
			 p = tree[p].r;
		}
	}
	else{
		if(tree[p].key > k)
		del(tree[p].l, k);
		else
		del(tree[p].r, k);
	}
}
int findmax(int p, int k){/*找出大于=k的最小值*/
	if(tree[p].key == k)
	return k;
	if(tree[p].l == 0 && tree[p].r == 0){
		if(tree[p].key > k)
		return tree[p].key;
		else
		return oo;
	}/*不断找到叶节点即可 找不到 就返回 oo -oo*/
	if(tree[p].key < k){/*小于K 答案肯定递归到右子树*/
		return findmax(tree[p].r, k);
	}
	else{
		int tmp = findmax(tree[p].l, k);
		return min(tmp, tree[p].key);/*如果> 就可能是答案 就要和 递归左子树 取 min*/
	}
}
int findmin(int p, int k){/*小于=k的最大值, 同 findmax*/
	if(tree[p].key == k)
	return k;
	if(tree[p].l == 0 && tree[p].r == 0){
		if(tree[p].key < k)
		return tree[p].key;
		else
		return -oo;
	}
	if(tree[p].key < k){
		int tmp = findmin(tree[p].r, k);
		return max(tmp, tree[p].key);
	}
	else
		return findmin(tree[p].l, k);
}
void display(int x){
	if(x == 0)
	return;
	printf("%d ", tree[x].key);
	display(tree[x].l);
	display(tree[x].r);
}
int main(){
	while(~scanf("%d%d", &n, &m)){
		cnt = root = tot = 0;
		insert(root, 0);
		insert(root, n + 1);
		for(int i = 0; i < m; i++){
			scanf("%s", s);
			int a;
			if(*s == 'D'){
				scanf("%d", &a);
				insert(root, a);
				st[++tot] = a;
			}
			else
				if(*s == 'Q'){
					scanf("%d", &a);
					int tr = findmax(root, a);
					int tl = findmin(root, a);
					if(tr == a)
					puts("0");
					else
					printf("%d\n", tr - tl - 1);
				}
				else{
					del(root, st[tot]);
					tot--;
				}
		}
	}
	return 0;

}

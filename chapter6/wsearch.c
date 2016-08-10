
#include "wsearch.h"


char *_strdup(char *s){
	char *p;

	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}


struct tnode *talloc(void){
	return (struct tnode *) malloc(sizeof(struct tnode));
}

void treeprint(struct tnode *p){
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

// recursive
struct tnode *addtree(struct tnode *p, char *w){
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = _strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}else if((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);

	return p;
}


int main(){
	print(BLU "running..." RESET);

	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);

	treeprint(root);
	return 0;
}
#ifndef MEMBER_H
#define MEMBER_H

typedef struct Member Member;
typedef struct MemberList MemberList;

struct Member
{
    char *name;
    struct Member *next; // pointeur vers le prochain membre
};

struct MemberList
{
    Member *first;
};

void listMembers(MemberList *members);

#endif
rows = int(input("Enter No of Rows"))
cols = int(input("Enter No of Cols"))
matrix=[]
print("Enter the elements of matrix")
for i in range(rows):
    row=list(map(int,input().split()))
    matrix.append(row)

print(matrix)

row=len(matrix)
col=len(matrix[0])
sparseM=[]

for i in range(rows):
    for j in range(cols):
        if matrix[i][j]!=0:
            sparseM.append([i,j,matrix[i][j]])
sparseM.insert(0,[row,col,len(sparseM)])

print(sparseM)
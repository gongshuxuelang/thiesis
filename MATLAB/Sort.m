A = [3,5,1;1,8,5;6,1,4;1,4,2;3,1,4;9,1,2;1,6,4;1,8,2];
B = A;
[length,line] = size(A);
for i = 1:length
    for j = i+1:length
        if A(i,1) > A(j,1)
            A([i j],:) = A([j i],:);
        end
    end
end

for i = 1:length
    for j = i+1:length
        if A(i,1) == A(j,1)
            if A(i,2) > A(j,2)
                A([i j],:) = A([j i],:);        
            end
        end
    end
end
for i = 1:length
    for j = i+1:length
        if A(i,1) == A(j,1)
            if A(i,2) == A(j,2)
                if A(i,3) > A(j,3)
                    A([i j],:) = A([j i],:);   
                end
            end
        end
    end
end
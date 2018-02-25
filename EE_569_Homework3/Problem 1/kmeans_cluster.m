%% For K-means clustering for texture segmentation
clc;
clear all;
close all;
f=csvread('energy_feature_vector1.csv');
[idx,C]=kmeans(f,6);
cluster=zeros();
f=fopen('E:/MATLAB2016/corner_cluster.txt','wt');

for i=1:206500
    cluster(i)=idx(i);
   fprintf(f,'%d',cluster(i));
    fprintf(f,',');
end

 fclose(f);
%[coeff,score,latent,tsquared,explained] = pca(f(:,1:3));
%% PCA for texture classification and texture segmentation
clc;
clear all;
close all;
feature_normalised=csvread('energy_feature_vector.csv');
feature_normalised1=csvread('energy_feature_vector_test.csv');
f=feature_normalised';
f1=feature_normalised1';
coeff1 = pca(f,'Algorithm','svd','NumComponents',3);
coeff2 = pca(f1,'Algorithm','svd','NumComponents',3);
%[C,idx]=kmeans(coeff1,4)
%kmeans(coeff2,4)
X=coeff1(:,1);
Y=coeff1(:,2);
Z=coeff1(:,3);

for i=1:4
    figure(1);
    if idx(i)==1;
scatter3(X,Y,Z,'r');
 end
    if idx(i)==2;
scatter3(X,Y,Z,'g');
 end
    if idx(i)==3;
scatter3(X,Y,Z,'b');
 end
    if idx(i)==4;
scatter3(X,Y,Z,'k');
   
    end
   
    end
    
title('scatter plot showing the clusters of the 12 trained images');
X1=coeff2(:,1);
Y1=coeff2(:,2);
Z1=coeff2(:,3);
figure(2);
scatter3(X1,Y1,Z1)
title('scatter plot showing the clusters of the 12 trained images');
%% Segmentation PCA 1-c
clc;
clear all;
close all;
feature_normalised=csvread('energy_feature_vector1.csv');
f=feature_normalised';
coeff1 = pca(f,'Algorithm','svd','NumComponents',3);
[C,idx]=kmeans(coeff1,5);
X=coeff1(:,1);
Y=coeff1(:,2);
Z=coeff1(:,3);
figure(1);
scatter3(X,Y,Z)
title('scatter plot showing the clusters of the 12 trained images');
cluster=zeros();
f=fopen('E:/MATLAB2016/corner_cluster1.txt','wt');

for i=1:206500
    cluster(i)=C(i);
   fprintf(f,'%d',cluster(i));
    fprintf(f,',');
end

 fclose(f);
%X1=coeff2(:,1);
%Y1=coeff2(:,2);
%Z1=coeff2(:,3);
%figure(2);
%scatter3(X1,Y1,Z1)
%title('scatter plot showing the clusters of the 12 trained images');
%% Histogram Generation of the 4 images
f1=csvread('histogram1.csv');
f2=csvread('histogram2.csv');
f3=csvread('histogram3.csv');
f4=csvread('histogram4.csv');
figure(1);
bar(f1);
title('Histogram of the Convertible_1');
figure(2);
bar(f2);
title('Histogram of the Truck');
figure(3);
bar(f3);
title('Histogram of the Convertible_2');
figure(4);
bar(f4);
title('Histogram of the SUV');
m1=pdist2(f1',f3','chisq')
m2=pdist2(f2',f3','chisq')
m3=pdist2(f4',f3','chisq')


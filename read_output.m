
load output1.dat;
%Unstable fraction
x = output1(:, 1);
y1 = output1(:, 2);
y2 = output1(:, 3);

plot(x,y1,'LineWidth',2);
title('Unstable fraction vs. p','fontsize',12);
xlabel('p','fontsize',12);
ylabel('Unstable fraction','fontsize',12); 
axis([0 50 0 1.1]);
box off;


%Stable number
figure; 
plot(x,y2,'LineWidth',2);
title('Stable number vs. p','fontsize',12);
xlabel('p','fontsize',12);
ylabel('Stable number','fontsize',12); 
axis([0 50 0 13]);
box off;


%Basin number
figure;
load output2.dat
x1 = output2(:, 1);
x2 = output2(:, 2);
y = output2(:, 3);

j = 1;
for i = 1 : 25
        plot(x2(j:j+49),y(j:j+49),'LineWidth',2);
        t = num2str(x1(j));
        a = y(j:j+49);
        inda = find(a==max(a));
        text(x2(inda(1)), max(a), strcat('p=',t));
        j = j + 50;
        hold on;
   
end
title('Basin number in different p patterns','fontsize',12);
xlabel('p','fontsize',12);
ylabel('Basin number','fontsize',12); 
axis([0 50 0 3]);
box off;


%Basin frequency
figure;
for i = 0 : 24
    for j = 1 : 50
        z(i*50 + j) = y(i*50 +j)/x1((i+1)*50);
    end
end
j = 1;
for i = 1 : 25
        plot(x2(j:j+49),z(j:j+49),'LineWidth',2);
        t = num2str(x1(j));
        a = z(j:j+49);
        inda = find(a==max(a));
        text(x2(inda(1)), max(a), strcat('p=',t));
        j = j + 50;
        hold on;
end
title('Basin frequency in different p patterns','fontsize',12);
xlabel('p','fontsize',12);
ylabel('Basin frequency','fontsize',12); 
axis([0 50 0 0.5]);
box off;

 

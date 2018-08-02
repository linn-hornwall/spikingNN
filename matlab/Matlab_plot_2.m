file1=fopen('sum_spikes2.txt','r');
formatSpec='%u %u';
sizeA=[2001 Inf];
A=fscanf(file1,formatSpec,sizeA);
fclose(file1);
A=A'
file2=fopen('spikes2.txt','r')
formatSpec='%u %u';
sizeB=[50 Inf];
B= fscanf(file2,formatSpec,sizeB);
fclose(file2);

subplot(2,1,2),stem(A,'k', 'Marker', 'none');
title('Sum of spikes at each time step')
xlabel('Timestep')
ylabel('Sum of spikes')
axis([1200 2000.8 0 1500])
set(gca,'yTick',0:500:1500)
set(gca,'xTick',1200:100:2000)

subplot(2,1,1);
size=5;
spy(B,'k',size);
pbaspect([5 1 1])
axis([1200 2000.8 0 50])
title('Number of neuron spiking at each time step')
set(gca,'Ydir','Normal')
set(gca,'yTick',0:10:50)
set(gca,'yTickLabel',{'0','10','20','30','40','50'})
set(gca,'xTick',0:100:20001)
xlabel('Timestep')
ylabel('Neurons that spike')
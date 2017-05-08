package prod_cons;

public class Main {
	
	public static void main(String[] args){
		
		Production product = new Production();
		Consumer consumer = new Consumer(product);
		Producer producer = new Producer(product);
				
		producer.start();
		consumer.start();		
	}

}

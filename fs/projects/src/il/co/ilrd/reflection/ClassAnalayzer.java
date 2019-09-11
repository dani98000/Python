package il.co.ilrd.reflection;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;

public class ClassAnalayzer {
    public static void main(String[] args) {
 
        Class<Foo> FooObj = Foo.class;
        try {
            // get the absolute name of the class
            String fooClassPackage = FooObj.getName();
            System.out.println("Class Name is: " + fooClassPackage);
 
            // get the simple name of the class (without package info)
            String fooClassNoPackage = FooObj.getSimpleName();
            System.out.println("Class Name without package is: "
                    + fooClassNoPackage);
 
            // get the package name of the class
            Package fooPackage = FooObj.getPackage();
            System.out.println("Package Name is: " + fooPackage);
 
            // get all the constructors of the class
            Constructor<?>[] constructors = FooObj.getConstructors();
            System.out.println("Constructors are: "
                    + Arrays.toString(constructors));
 
            // get all methods of the class including declared methods of superclasses
            // in that case, superclass of fooInstanceCar is the class java.lang.Object
            Method[] allmethods = FooObj.getMethods();
            System.out.println("Methods are: " + Arrays.toString(allmethods));
            for (Method method : allmethods) {
                System.out.println("method = " + method.getName());
            }
 
            // get all methods declared in the class
            // but excludes inherited methods.
            Method[] declaredMethods = FooObj.getDeclaredMethods();
            System.out.println("Declared Methods are: "
                    + Arrays.toString(declaredMethods));
            for (Method dmethod : declaredMethods) {
                System.out.println("method = " + dmethod.getName());
            }
 
            // get method with specific name and parameters
            Method oneMethod = FooObj.getMethod("getAge");
            System.out.println("Method is: " + oneMethod);
             
            Object fooInstance1 = FooObj.getConstructor(Integer.TYPE, Integer.TYPE).newInstance(15,318820131);
            
            Constructor<?>[] constructorsArray = FooObj.getConstructors();
            for (Constructor ctr : constructorsArray) {
                // get public field name
                System.out.println("constructor is: " + ctr.getName());
                System.out.println(": " + ctr.toGenericString());

            }
            
            oneMethod.invoke(fooInstance1);
 
            Class<?>[] parameterTypes = oneMethod.getParameterTypes();
            System.out.println("Parameter types of setAge() are: "
                    + Arrays.toString(parameterTypes));
 
            Class<?> returnType = oneMethod.getReturnType();
            System.out.println("Return type is: " + returnType);
 
            Field[] fields = FooObj.getFields();
 
            System.out.println("Public Fields are: ");
            for (Field oneField : fields) {
                // get public field name
                Field field = FooObj.getField(oneField.getName());
                String fieldname = field.getName();
                System.out.println("Fieldname is: " + fieldname);
 
                // get public field type
                Object fieldType = field.getType();
                System.out.println("Type of field " + fieldname + " is: "
                        + fieldType);
 
                // get public field value
                Object value = field.get(fooInstance1);
                System.out.println("Value of field " + fieldname + " is: "
                        + value);
 
            }
 
            Field privateField = FooObj.getDeclaredField("age");
 
            String name = privateField.getName();
            System.out.println("One private Fieldname is: " + name);
            
            privateField.setAccessible(true);
 
            // get the value of this private field
            int fieldValue = (int) privateField.get(fooInstance1);
            System.out.println("fieldValue = " + fieldValue);
 
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
}
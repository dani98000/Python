package il.co.ilrd.util;
import java.security.Key;
import java.util.Date;

import javax.servlet.http.HttpServletRequest;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import io.jsonwebtoken.security.Keys;

public class JwtUtil {
    private static final String REDIS_SET_ACTIVE_SUBJECTS = "active-subjects";

    public static String generateToken(String signingKey, String subject) {
        long nowMillis = System.currentTimeMillis();
        Date now = new Date(nowMillis);
        System.out.println("Subject: " + subject);
        
        String token = Jwts.builder()
        			.setSubject(subject)
        			.signWith(SignatureAlgorithm.HS256, signingKey)
        			.setIssuedAt(now)
        			.compact();
        
        System.out.println("jwt reached4");
        RedisUtil.INSTANCE.add(REDIS_SET_ACTIVE_SUBJECTS, subject);

        return token;
    }

    public static String parseToken(HttpServletRequest httpServletRequest, String jwtTokenCookieName, String signingKey){
        String token = CookieUtil.getValue(httpServletRequest, jwtTokenCookieName);
        if(token == null) {
            return null;
        }

        String subject = Jwts.parser().setSigningKey(signingKey).parseClaimsJws(token).getBody().getSubject();
        if (!RedisUtil.INSTANCE.isMember(REDIS_SET_ACTIVE_SUBJECTS, subject)) {
            return null;
        }

        return subject;
    }
    
    public static boolean validateToken(String token, String signingKey) {
    	if(token == null) {
            return false;
        }

        String subject = Jwts.parser().setSigningKey(signingKey).parseClaimsJws(token).getBody().getSubject();

        return RedisUtil.INSTANCE.isMember(REDIS_SET_ACTIVE_SUBJECTS, subject);
    }

    public static void invalidateRelatedTokens(HttpServletRequest httpServletRequest) {
        RedisUtil.INSTANCE.remove(REDIS_SET_ACTIVE_SUBJECTS, (String) httpServletRequest.getAttribute("companyName"));
    }
    
    public static void invalidateRelatedTokens(final String token) {
        RedisUtil.INSTANCE.remove(REDIS_SET_ACTIVE_SUBJECTS, token);
    }
}